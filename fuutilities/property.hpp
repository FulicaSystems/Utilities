#pragma once

#include <cassert>
#include <functional>

namespace Utils
{
template <class TType> class [[deprecated("Use getters and setters instead")]] Property
{
  private:
    std::function<const TType &()> getAccessor;
    std::function<void(const TType &t)> setAccessor;

  public:
    Property() = delete;
    Property(std::function<const TType &()> get, std::function<void(const TType &t)> set);

    // get accessor
    const TType &get() const
    {
        assert(getAccessor && "Get accessor not set");
        return getAccessor();
    }
    operator const TType &() const
    {
        return get();
    }

    // set accessor
    void set(const TType &t)
    {
        assert(setAccessor && "Set accessor not set");
        setAccessor(t);
    }
    void operator=(const TType &t)
    {
        set(t);
    }
};
} // namespace Utils

template <class TType>
inline Utils::Property<TType>::Property(std::function<const TType &()> get, std::function<void(const TType &t)> set)
    : getAccessor(get), setAccessor(set)
{
}