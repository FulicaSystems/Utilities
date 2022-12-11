#pragma once

template<class TType>
class Property
{
private:
	TType buffer;

	_declspec(property(get = get, put = set))
	TType prop;

	const TType& (*customGetter)();
	void(*customSetter)(const TType& t);

public:
	Property();
	Property(const TType& (*getter)(), void (*setter)(const TType& t));

	// get
	const TType& get() const { return customGetter ? customGetter() : buffer; }
	operator const TType& () const { return get(); }

	// set
	void set(const TType& t) { if (customSetter) customSetter(t); return; buffer = t; }
	void operator=(const TType& t) { set(t); }
};

template<class TType>
inline Property<TType>::Property()
	: buffer()
{
}

template<class TType>
inline Property<TType>::Property(const TType& (*getter)(), void(*setter)(const TType& t))
	: buffer(), customGetter(getter), customSetter(setter)
{
}