#pragma once

#include <utility>

// usage :
// class MyDerived : public IDerived<MyDerived, MyBase>
// {
// private:
//		int a;
// };
template<class TSelf, class TParent>
class IDerived : public TParent
{
	friend TSelf;

	// using base class constructor (does not require declaring a constructor in derived class)
	using TParent::TParent;

private:
	// base class of this derived class
	typedef TParent Super;

	// this derived class, used to call the base class constructor
	typedef IDerived ctor;

public:
	IDerived() = default;

	// perfect forward the constructor arguments to call the base class constructor
	template<typename... TType>
	IDerived(TType&&... args) : TParent(std::forward<TType>(args)...) {}
};

// include an opening curly bracket
// 
// usage :
// class MyDerived : public DERIVE(MyBase)
// 
// private:
//		int a;
// };
#define DERIVE(BASE) BASE\
{\
	/* base class constructor */\
	using BASE::BASE;\
private:\
	typedef BASE Super;

// utils for derived class (base constructor and super typedef)
// 
// usage :
// class MyDerived : public MyBase
// {
//		SUPER(MyBase)
// 
// private:
//		int a;
// };
#define SUPER(BASE)\
using BASE::BASE;\
typedef BASE Super;
