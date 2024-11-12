#pragma once

#include <memory>

namespace Utils
{
	/**
	 * Creating a Singleton class.
	 *
	 * @code
	 * class T : public Singleton<T>
	 * {
	 *		SINGLETON(T)
	 *
	 * public:
	 * 		static void foo()
	 * 		{
	 * 			T& t = getInstance();
	 * 		}
	 * };
	 * @endcode
	 */
	template<class T>
	class Singleton
	{
	private:
		static std::unique_ptr<T> instance;

	protected:
		Singleton() = default;

		/**
		 * Get the unique instance.
		 *
		 * @return
		 */
		static inline T& getInstance();

	public:
		/**
		 * No copy constructor.
		 */
		Singleton(const T& t) = delete;
		/**
		 * No copy constructor.
		 */
		Singleton(const Singleton& s) = delete;

		/**
		 * No assignment.
		 */
		void operator=(const T& t) = delete;
		/**
		 * No assignment.
		 */
		void operator=(const Singleton& s) = delete;
	};
}

template<class T>
std::unique_ptr<T> Utils::Singleton<T>::instance(new T());

template<class T>
inline T& Utils::Singleton<T>::getInstance()
{
	return *instance.get();
}

#define SINGLETON(CLASS)\
friend class Utils::Singleton<CLASS>;\
/* Cannot create a singleton derived object (private constructor) */\
private:\
CLASS() = default;
