#pragma once

#include <functional>

namespace Utils
{
#ifdef OLD_TASK
	class Task
	{
	private:
		std::function<void()> task;

	public:
		Task() = default;

		/**
		 * Create a task using a function.
		 *
		 * @param fct
		 */
		Task(std::function<void()> fct);

		/**
		 * Run the function.
		 *
		 */
		void doTask();
	};
#else
	using Task = std::function<void()>;
#endif
}