#include <iostream>

#include <chrono>

#include "utils/multithread/threadpool.hpp"

Utils::ThreadPool::ThreadPool(uint nThreads)
{
	for (uint i = 0; i < nThreads; ++i)
	{
		threads.emplace_back(std::bind(&ThreadPool::poolRoutine, this, i));
		// the threads are not working yet
		workers.emplace_back(false);
	}

	running.test_and_set();
}

Utils::ThreadPool::~ThreadPool()
{
	if (running.test())
	{
		while (!isIdle()) // wait for the last workers
		{
			// finish main tasks while parallel threads are working
			pollMainQueue();

			std::this_thread::yield();
		}

		running.clear();
	}

	// finish last main tasks;
	pollMainQueue();

	workerCV.notify_all();	// wake all workers
	// jthreads are auto joining
	threads.clear();
}

void Utils::ThreadPool::addTask(std::function<void()> fct, const bool parallel)
{
	if (parallel)
	{
		std::lock_guard<std::mutex> guard(workerQueueMX);
		workerQueue.emplace_back(fct);
		workerCV.notify_one();
	}
	else
	{
		std::lock_guard<std::mutex> guard(mainQueueMX);
		mainQueue.emplace_back(fct);
	}
}

void Utils::ThreadPool::poolRoutine(int id)
{
	while (running.test())
	{
		if (workerQueue.empty())
		{
			// block this thread until worker queue is not empty anymore, unlock if app is not running
			std::unique_lock<std::mutex> lock(workerQueueMX);
			workerCV.wait(lock, [&]() -> bool {
				return !running.test() || !workerQueue.empty();
				});

			continue;
		}

		Task t;
		{
			std::lock_guard<std::mutex> guard(workerQueueMX);

			t = workerQueue.front();
			workerQueue.pop_front();
		}
		workers[id] = true;	// this thread is working
		t();
		workers[id] = false;

		auto now = (float)std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::steady_clock::now().time_since_epoch()).count();
		lastTaskTime.store(now);

		//printThreadId(id);
	}
}

void Utils::ThreadPool::pollMainQueue()
{
	std::lock_guard<std::mutex> guard(mainQueueMX);

	while (!mainQueue.empty())
	{
		mainQueue.front()();
		mainQueue.pop_front();
	}
}

bool Utils::ThreadPool::isIdle()
{
	if (!workerQueue.empty())
		return false;

	for (const bool working : workers)
	{
		if (working)
			return false;
	}

	return true;
}

void Utils::ThreadPool::printThreadId(int id)
{
	std::lock_guard<std::mutex> guard(printMX);
	std::cout << "thread #" << id << std::endl;
}