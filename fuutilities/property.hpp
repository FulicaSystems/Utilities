#pragma once

#include <cassert>
#include <functional>

namespace Utils
{
enum AccessorFlagE
{
    GET = 1 << 0,
    SET = 1 << 1,
    RW = GET | SET,

    CUSTOM_GET = 1 << 2,
    CUSTOM_SET = 1 << 3,
    CUSTOM = CUSTOM_GET | CUSTOM_SET,
};

template <typename TType, unsigned int NAccessorFlag> class Property
{
  private:
    std::function<const TType &()> getAccessor;
    std::function<void(const TType &t)> setAccessor;

  public:
    Property() = delete;

    Property(const Property &) = delete;
    Property &operator=(const Property &) = delete;
    Property(Property &&) = delete;
    Property &operator=(Property &&) = delete;

    ~Property() = default;

    Property(TType &var);

    // get accessor
    const TType &get() const
    {
        static_assert(NAccessorFlag & AccessorFlagE::GET, "Get accessor must be valid");
        return getAccessor();
    }
    operator const TType &() const
    {
        return get();
    }

    // set accessor
    void set(const TType &t)
    {
        static_assert(NAccessorFlag & AccessorFlagE::SET, "Set accessor must be valid");
        setAccessor(t);
    }
    void operator=(const TType &t)
    {
        set(t);
    }
};
} // namespace Utils

template <class TType, unsigned int NAccessorFlag> inline Utils::Property<TType, NAccessorFlag>::Property(TType &var)
{
    if (NAccessorFlag & AccessorFlagE::GET)
        getAccessor = [&]() -> const TType & { return var; };
    if (NAccessorFlag & AccessorFlagE::SET)
        setAccessor = [&](const TType &value) { var = value; };
}
