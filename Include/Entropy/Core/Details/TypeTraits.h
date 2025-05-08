// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

#include <functional>
#include <type_traits>

namespace Entropy
{

namespace Traits
{

template <typename T>
using RemoveConstRef_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

//--------------

template <typename T>
class HasBaseClass
{
    template <typename U>
    static std::true_type Exists(typename U::EntropySuper*);
    template <typename>
    static std::false_type Exists(...);

    typedef decltype(Exists<RemoveConstRef_t<T>>(nullptr)) ResultType; // NOLINT

public:
    static constexpr bool value = ResultType::value;
};

#if __cplusplus >= 201300
template <class T>
constexpr bool HasBaseClass_v = HasBaseClass<T>::value;
#endif

//---------------

template <typename T, typename = void>
struct BaseClassOf
{
    using Type = void;
};

template <typename T>
struct BaseClassOf<T, typename std::enable_if<HasBaseClass<T>::value>::type>
{
    using Type = typename RemoveConstRef_t<T>::EntropySuper;
};

template <typename T, typename = void>
struct BaseClassWithQualifiersOf
{
    using Type = void;
};

template <typename T>
struct BaseClassWithQualifiersOf<T, typename std::enable_if<!std::is_const<T>::value && !std::is_reference<T>::value &&
                                                            HasBaseClass<T>::value>::type>
{
    using Type = typename T::EntropySuper;
};

template <typename T>
struct BaseClassWithQualifiersOf<const T, typename std::enable_if<HasBaseClass<T>::value>::type>
{
    using Type = const typename BaseClassWithQualifiersOf<typename std::remove_const<T>::type>::Type;
};

template <typename T>
struct BaseClassWithQualifiersOf<T&, typename std::enable_if<HasBaseClass<T>::value>::type>
{
    using Type = typename BaseClassWithQualifiersOf<typename std::remove_reference<T>::type>::Type&;
};

template <class T>
using BaseClassOf_t = typename BaseClassOf<T>::Type;

template <class T>
using BaseClassWithQualifiersOf_t = typename BaseClassWithQualifiersOf<T>::Type;

//==========================

template <typename TFunc, typename... TArgs>
class IsInvocable
{
    template <typename UFunc, typename... UArgs>
    static auto CanCall(UFunc&& p) -> decltype(p(std::declval<UArgs>()...), std::true_type());
    template <typename, typename...>
    static std::false_type CanCall(...);

    typedef decltype(CanCall<TFunc, TArgs...>(std::declval<TFunc>())) ResultType; // NOLINT

public:
    static constexpr bool value = ResultType::value;
};

#if __cplusplus >= 201300
template <typename F, typename... Args>
constexpr bool IsInvocable_v = IsInvocable<F, Args...>::value;
#endif

//------

template <typename TClass, typename TMethod, typename... TArgs>
class IsClassMethodInvocable
{
    template <typename UClass, typename UMethod, typename... UArgs>
    static auto CanCall(UClass&& c, UMethod&& m) -> decltype((c.*m)(std::declval<UArgs>()...), std::true_type());
    template <typename, typename...>
    static std::false_type CanCall(...);

    typedef decltype(CanCall<TClass, TMethod, TArgs...>(std::declval<TClass>(),
                                                        std::declval<TMethod>())) ResultType; // NOLINT

public:
    static constexpr bool value = ResultType::value;
};

#if __cplusplus >= 201300
template <typename C, typename M, typename... Args>
constexpr bool IsClassMethodInvocable_v = IsClassMethodInvocable<C, M, Args...>::value;
#endif

//==========================

// Turns a type like "const T*&" into simply "T".

template <typename T, typename = void>
struct UnqualifiedType
{
    using type = T;
};

template <typename T>
struct UnqualifiedType<T,
                       typename std::enable_if<std::is_const<T>::value || std::is_pointer<T>::value ||
                                               std::is_reference<T>::value || std::is_rvalue_reference<T>::value>::type>
{
    using type = typename UnqualifiedType<typename std::remove_const<
        typename std::remove_pointer<typename std::remove_reference<T>::type>::type>::type>::type;
};

template <typename T>
using UnqualifiedType_t = typename UnqualifiedType<T>::type;

//============================

template <typename T, typename = void>
struct IsUnqualifiedType : std::true_type
{
};

template <typename T>
struct IsUnqualifiedType<T, typename std::enable_if<std::is_const<T>::value || std::is_pointer<T>::value ||
                                                    std::is_reference<T>::value>::type> : std::false_type
{
};

#ifdef ENTROPY_CPP14
template <typename T>
constexpr bool IsUnqualifiedType_v = IsUnqualifiedType<T>::value;

template <typename T>
constexpr bool IsQualifiedType_v = !IsUnqualifiedType_v<T>;
#endif

//============================

namespace details
{

template <typename T>
struct CanCompareAgainstNull
{
private:
    template <typename U>
    static auto Exists(int) -> decltype(std::declval<U>() == nullptr, std::true_type{});

    template <typename>
    static std::false_type Exists(...);

public:
    static constexpr bool value = decltype(Exists<T>(0))::value;
};

template <typename T, typename = void>
struct IsNullCheck
{
    inline bool operator()(const T& val) const { return (val == nullptr); }
};

template <typename T>
struct IsNullCheck<T, typename std::enable_if<!CanCompareAgainstNull<T>::value>::type>
{
    inline constexpr bool operator()(const T& val) const { return false; }
};

} // namespace details

template <typename T>
inline bool IsNull(const T& val)
{
    return details::IsNullCheck<T>{}(val);
}

} // namespace Traits

} // namespace Entropy

#ifndef ENTROPY_CPP14
namespace std
{
template <class _Ty, _Ty... _Vals>
struct integer_sequence
{ // sequence of integer parameters
    static_assert(is_integral<_Ty>::value, "integer_sequence<T, I...> requires T to be an integral type.");

    using value_type = _Ty;

    static constexpr size_t size() noexcept { return sizeof...(_Vals); }
};

template <class _Ty, _Ty _Size>
using make_integer_sequence = __make_integer_seq<integer_sequence, _Ty, _Size>;

template <size_t... _Vals>
using index_sequence = integer_sequence<size_t, _Vals...>;

template <size_t _Size>
using make_index_sequence = make_integer_sequence<size_t, _Size>;

template <class... _Types>
using index_sequence_for = make_index_sequence<sizeof...(_Types)>;
} // namespace std
#endif