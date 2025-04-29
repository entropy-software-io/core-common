// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

namespace Entropy
{

/// <summary>
/// Creates a strongly typed alias for a primitive type.
/// </summary>
/// <remarks>
/// This struct can be defined using 'struct %MyTypeName%Tag' for TName,
/// but unless the tag struct exists, the alias can't be used for
/// reflection. Therefore, it is preferable to use the DEFINE_STRONG_ALIAS
/// macro, which defines the tag struct too.
/// </remarks>
template <typename TValue, typename TName>
struct StrongAlias
{
    using UnderlyingType = TValue;

    constexpr StrongAlias() noexcept                   = default;
    constexpr StrongAlias(const StrongAlias&) noexcept = default;
    constexpr StrongAlias(StrongAlias&&) noexcept      = default;

    constexpr StrongAlias(const TValue& value) noexcept
        : _value(value)
    {
        AssertSize();
    }

    constexpr StrongAlias(TValue&& value) noexcept(std::is_nothrow_move_constructible<TValue>::value)
        : _value(std::move(value))
    {
        AssertSize();
    }

    inline constexpr operator TValue&() noexcept { return _value; }
    inline constexpr operator const TValue&() const noexcept { return _value; }

    inline constexpr const TValue& GetValue() const noexcept { return _value; }
    inline constexpr TValue& GetValueRW() noexcept { return _value; }
    inline constexpr void SetValue(const TValue& val) { _value = val; }

    inline friend void swap(StrongAlias& a, StrongAlias& b) noexcept
    {
        std::swap(static_cast<TValue&>(a), static_cast<TValue&>(b));
    }

    inline constexpr StrongAlias& operator=(const StrongAlias&) noexcept = default;
    inline constexpr StrongAlias& operator=(StrongAlias&&) noexcept      = default;

    inline constexpr bool operator==(const StrongAlias& other) const noexcept { return (_value == other._value); }
    inline constexpr bool operator!=(const StrongAlias& other) const noexcept { return !(*this == other); }
    inline constexpr bool operator<(const StrongAlias& other) const noexcept { return (_value < other._value); }
    inline constexpr bool operator<=(const StrongAlias& other) const noexcept { return (_value <= other._value); }
    inline constexpr bool operator>(const StrongAlias& other) const noexcept { return (_value > other._value); }
    inline constexpr bool operator>=(const StrongAlias& other) const noexcept { return (_value >= other._value); }

    inline constexpr bool operator==(const TValue& other) const noexcept { return (_value == other); }
    inline constexpr bool operator!=(const TValue& other) const noexcept { return !(*this == other); }
    inline constexpr bool operator<(const TValue& other) const noexcept { return (_value < other); }
    inline constexpr bool operator<=(const TValue& other) const noexcept { return (_value <= other); }
    inline constexpr bool operator>(const TValue& other) const noexcept { return (_value > other); }
    inline constexpr bool operator>=(const TValue& other) const noexcept { return (_value >= other); }

protected:
    TValue _value{};

    static constexpr void AssertSize()
    {
        static_assert(sizeof(StrongAlias) == sizeof(TValue), "Type size is not what was expected");
    }
};

template <typename T, typename = void>
struct UnderlyingType
{
    using Type = T;
};

template <typename TValue, typename TName>
struct UnderlyingType<StrongAlias<TValue, TName>>
{
    using Type = typename StrongAlias<TValue, TName>::UnderlyingType;
};

template <typename T>
using UnderlyingType_t = typename UnderlyingType<T>::Type;

} // namespace Entropy

namespace std
{

// Allow hashing
template <typename TValue, typename TName>
struct hash<Entropy::StrongAlias<TValue, TName>>
{
    size_t operator()(const Entropy::StrongAlias<TValue, TName>& k) const { return hash<TValue>{}(k.GetValue()); }
};

} // namespace std

#define ENTROPY_DEFINE_STRONG_ALIAS(name, type)                                                                        \
    struct name##_StrongAliasTag                                                                                       \
    {                                                                                                                  \
    };                                                                                                                 \
    using name = ::Entropy::StrongAlias<type, struct name##_StrongAliasTag>;
