#pragma once

#include <thread>
#include <atomic>
#include <deque>
#include <mutex>
#include <condition_variable>

#include "numerics.hpp"

#include "utils/multithread/task.hpp"

// define this macro to create a singleton threadpool
// #define THREADPOOL_SINGLETON
#ifdef THREADPOOL_SINGLETON
#include "utils/singleton.hpp"
#endif

namespace Utils
{
	class ThreadPool
	{
	private:
		std::deque<std::jthread>	threads;
		// thread-assigned bool to keep track of working threads
		std::deque<bool>			workers;

		// timing
		float						startTime = 0.f;
		float						endTime = 0.f;
		std::atomic<float>			lastTaskTime;


		// shared data

		// parallel tasks
		std::deque<Task>			workerQueue;
		// main thread tasks
		std::deque<Task>			mainQueue;

		// task queue mutex (used for workerTasks)
		std::mutex					workerQueueMX;
		// task queue mutex (used for mainQueue)
		std::mutex					mainQueueMX;
		// print mutex
		std::mutex					printMX;

		std::condition_variable		workerCV;

		// is the work routine running?
		std::atomic_flag			running = ATOMIC_FLAG_INIT;

		/**
		 * Thread routine.
		 *
		 * @param id
		 */
		void threadLoop(int id);

		/**
		 * Is the pool idling/ready.
		 */
		bool isIdle();

		/**
		 * Print the thread id.
		 *
		 * @param id
		 */
		void printThreadId(int id);

	public:
		/**
		 * Create the thread pool.
		 * Specify the number of threads, the number of threads is by default the maximum that the machine can get.
		 *
		 * @param nThreads
		 */
		ThreadPool(unsigned int nThreads = std::thread::hardware_concurrency());

		/**
		 * End the thread pool.
		 *
		 */
		~ThreadPool();

		/**
		 * Add a task to the task queue.
		 *
		 * @param fct
		 */
		void addTask(std::function<void()> fct, const bool parallel = true);

		/**
		 * Do every task from main queue. Recursive tasks are not possible
		 */
		void pollMainQueue();

		void launchThreads(const int num = 1);

		void killThreads(const int num = 1);
	};

#ifdef THREADPOOL_SINGLETON
	// TODO : rename to increase readability (Parallel::LaunchTask([](){});)
	class GlobalThreadPool : public Utils::Singleton<GlobalThreadPool>
	{
		SINGLETON(GlobalThreadPool)

	private:
		ThreadPool pool;

	public:
		static void addTask(const std::function<void()>& fct, const bool parallel = true)
		{
			getInstance().pool.addTask(fct, parallel);
		}

		static void pollMainQueue()
		{
			getInstance().pool.pollMainQueue();
		}
	};
#endif
}