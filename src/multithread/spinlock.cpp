#include <thread>
#include <chrono>

#include "utils/multithread/spinlock.hpp"

void Utils::SpinLock::lock()
{
	while (flag.test_and_set())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Utils::SpinLock::unlock()
{
	flag.clear();
}