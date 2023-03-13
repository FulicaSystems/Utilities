#include <iostream>

#include <chrono>

#include "utils/multithread/threadpool.hpp"

Utils::ThreadPool::ThreadPool(uint nThreads)
{
	for (uint i = 0; i < nThreads; ++i)
	{
		threads.push_back(std::jthread(std::bind(&ThreadPool::poolRoutine, this, i)));
	}

	running.store(true);
}

Utils::ThreadPool::~ThreadPool()
{
	if (running.load())
	{
		while (!workerQueue.empty())
			std::this_thread::yield();

		running.store(false);
	}

	threads.clear();
}

void Utils::ThreadPool::addTask(std::function<void()> fct)
{
	std::lock_guard<std::mutex> guard(workerQueueMX);

	workerQueue.push_back(Task(fct));
}

void Utils::ThreadPool::poolRoutine(int id)
{
	while (running.load())
	{
		if (workerQueue.empty())
			continue;

		Task t;
		{
			std::lock_guard<std::mutex> guard(workerQueueMX);

			t = workerQueue.front();
			workerQueue.pop_front();
		}
		t();

		auto now = (float)std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::steady_clock::now().time_since_epoch()).count();
		lastTaskTime.store(now);
		
		//printThreadId(id);
	}
}

void Utils::ThreadPool::printThreadId(int id)
{
	std::lock_guard<std::mutex> guard(printMX);
	std::cout << "thread #" << id << std::endl;
}

void Utils::ThreadPool::setStartTime()
{
	startTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now().time_since_epoch()).count();
}

float Utils::ThreadPool::getLoadingTime()
{
	endTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now().time_since_epoch()).count();

	return (endTime - startTime) / 1000.f;
}

float Utils::ThreadPool::printLastWorkingTime()
{
	if (lastTaskTime == 0.f)
		return 0.f;

	return (lastTaskTime - startTime) / 1000.f;
}

float Utils::ThreadPool::printLastWorkingTimeOnce()
{
	if (lastTaskTime == 0.f)
		return 0.f;

	float val = (lastTaskTime - startTime) / 1000.f;
	std::lock_guard<std::mutex> guard(printMX);
	std::cout << "LOADING TIME : " << val << "s" << std::endl;
	lastTaskTime = 0.f;

	return val;
}