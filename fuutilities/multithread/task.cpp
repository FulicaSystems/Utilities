#include "task.hpp"

#ifdef OLD_TASK
Utils::Task::Task(std::function<void()> fct)
	: task(fct)
{
}

void Utils::Task::doTask()
{
	if (task)
		task();
}
#endif