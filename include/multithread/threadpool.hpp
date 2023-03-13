#pragma once

#include <thread>
#include <atomic>
#include <deque>
#include <mutex>

#include "numerics.hpp"

#include "utils/multithread/task.hpp"
#include "utils/multithread/spinlock.hpp"

namespace Utils
{
	class ThreadPool
	{
	private:
		std::vector<std::jthread>	threads;

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
		// print mutex
		std::mutex					printMX;

		// is the work routine running?
		std::atomic<bool>			running;

	public:
		/**
		 * Create the thread pool.
		 * Specify the number of threads, the number of threads is by default the maximum that the machine can get.
		 * 
		 * @param nThreads
		 */
		ThreadPool(uint nThreads = std::thread::hardware_concurrency());

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
		void addTask(std::function<void()> fct);

		/**
		 * Thread routine.
		 * Main loop function
		 * 
		 * @param id
		 */
		void poolRoutine(int id);

		/**
		 * Print the thread id.
		 * 
		 * @param id
		 */
		void printThreadId(int id);

		/**
		 * Get the time to store as the thread pool's starting time.
		 * 
		 */
		void setStartTime();

		/**
		 * Return the time between now and the start time.
		 * Equivalent to a loading time.
		 * The user chooses when to show the loading time, do not forget to set the start time.
		 */
		float getLoadingTime();

		/**
		 * Time when the pool has finished doing every tasks.
		 */
		float printLastWorkingTime();

		/**
		 * Print the time when the last task was finished.
		 * 
		 * @return 
		 */
		float printLastWorkingTimeOnce();
	};
}