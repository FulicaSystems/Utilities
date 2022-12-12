#pragma once

#include <functional>

template<class TType>
class Property
{
private:
	std::function<const TType& ()> userGet;
	std::function<void(const TType& t)> userSet;

public:
	Property(std::function<const TType& ()> getAccessor,
		std::function<void(const TType& t)> setAccessor);

	// get accessor
	const TType& get() const { assert(("Get accessor not set", userGet)); return userGet(); }
	operator const TType& () const { return get(); }

	// set accessor
	void set(const TType& t) { assert(("Set accessor not set", userSet)); userSet(t); }
	void operator=(const TType& t) { set(t); }
};

template<class TType>
inline Property<TType>::Property(std::function<const TType& ()> getAccessor,
	std::function<void(const TType& t)> setAccessor)
	: userGet(getAccessor), userSet(setAccessor)
{
}