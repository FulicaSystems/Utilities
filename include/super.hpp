#pragma once

template<class TSelf, class TParent>
class IDerived : public TParent
{
	friend TSelf;

private:
	typedef TParent Super;
};