#pragma once

#include <atomic>

namespace Utils
{
	class SpinLock
	{
	private:
		std::atomic_flag flag = ATOMIC_FLAG_INIT;

	public:
		/**
		 * Lock the spin lock.
		 *
		 */
		void lock();

		/**
		 * Unlock the spin lock.
		 *
		 */
		void unlock();
	};
}