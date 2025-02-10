#pragma once

#include <functional>
#include <cassert>

namespace Utils
{
	// TODO : template <unsigned int N> for default accessors
	// Property<MyType, GET>
	// Property<MyType, SET>
	// Property<MyType, GET | SET>
	// Property<MyType, CUSTOM>
	// TODO : make default accessors (as macro ?)
	// Utils::Property<int> p{[this]() -> const int & { return a; }, [this](const int &i) { a = i; }};
        // Utils::Property<int> p2{[this]() -> const int & { return a; }, nullptr};
	template<class TType>
	class Property
	{
	private:
		std::function<const TType& ()> getAccessor;
		std::function<void(const TType& t)> setAccessor;

	public:
		Property() = delete;
		Property(std::function<const TType& ()> get,
			std::function<void(const TType& t)> set);

		// get accessor
		const TType& get() const { assert(getAccessor && "Get accessor not set"); return getAccessor(); }
		operator const TType& () const { return get(); }

		// set accessor
		void set(const TType& t) { assert(setAccessor && "Set accessor not set"); setAccessor(t); }
		void operator=(const TType& t) { set(t); }
	};
}

template<class TType>
inline Utils::Property<TType>::Property(std::function<const TType& ()> get,
	std::function<void(const TType& t)> set)
	: getAccessor(get), setAccessor(set)
{
}
