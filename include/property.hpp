#pragma once

template<class TType>
class Property
{
private:
	const TType& (*userGet)();
	void(*userSet)(const TType& t);

public:
	Property(const TType& (*getAccessor)(), void (*setAccessor)(const TType& t));

	// get accessor
	const TType& get() const { if (userGet) return userGet(); throw std::exception("Get accessor not set"); }
	operator const TType& () const { return get(); }

	// set accessor
	void set(const TType& t) { if (userSet) userSet(t); else throw std::exception("Set accessor not set"); }
	void operator=(const TType& t) { set(t); }
};

template<class TType>
inline Property<TType>::Property(const TType& (*getAccessor)(), void(*setAccessor)(const TType& t))
	: userGet(getAccessor), userSet(setAccessor)
{
}