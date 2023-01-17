#pragma once

#include <functional>

namespace Utils
{
	template<class TType>
	class Property
	{
	private:
		std::function<const TType& ()> getAccessor;
		std::function<void(const TType& t)> setAccessor;

	public:
		Property(std::function<const TType& ()> get,
			std::function<void(const TType& t)> set);

		// get accessor
		const TType& get() const { assert(("Get accessor not set", getAccessor)); return getAccessor(); }
		operator const TType& () const { return get(); }

		// set accessor
		void set(const TType& t) { assert(("Set accessor not set", setAccessor)); setAccessor(t); }
		void operator=(const TType& t) { set(t); }
	};
}

template<class TType>
inline Utils::Property<TType>::Property(std::function<const TType& ()> get,
	std::function<void(const TType& t)> set)
	: getAccessor(get), setAccessor(set)
{
}