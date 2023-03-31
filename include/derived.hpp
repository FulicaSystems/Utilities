#pragma once

#include <utility>

template<class TSelf, class TParent>
class IDerived : public TParent
{
	friend TSelf;

private:
	// base class of this derived class
	typedef TParent Super;

	// this derived class, used to call the base class' constructor
	typedef IDerived ctor;

public:
	IDerived() = default;

	// perfect forward the constructor arguments to call the base class' constructor
	template<typename... TType>
	IDerived(TType&&... args) : TParent(std::forward<TType>(args)...) {}
};