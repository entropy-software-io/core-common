// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

#include <functional>
#include <type_traits>

#ifndef ENTROPY_REMOVE_CONST_REF
#define ENTROPY_REMOVE_CONST_REF(type) std::remove_cv_t<std::remove_reference_t<type>>
#endif

namespace Entropy
{

namespace Traits
{

template <typename T>
class HasBaseClass
{
    template <typename U>
    static std::true_type Exists(typename U::EntropySuper*);
    template <typename>
    static std::false_type Exists(...);

    typedef decltype(Exists<ENTROPY_REMOVE_CONST_REF(T)>(nullptr)) ResultType; // NOLINT

public:
    static constexpr bool cValue = ResultType::value;
};

template <class T>
constexpr bool HasBaseClass_v = HasBaseClass<T>::cValue;

//---------------

template <typename T, typename = void>
struct BaseClassOf
{
    using Type = void;
};

template <typename T>
struct BaseClassOf<T, std::enable_if_t<HasBaseClass_v<T>>>
{
    using Type = typename ENTROPY_REMOVE_CONST_REF(T)::EntropySuper;
};

template <typename T, typename = void>
struct BaseClassWithQualifiersOf
{
    using Type = void;
};

template <typename T>
struct BaseClassWithQualifiersOf<T,
                                 std::enable_if_t<!std::is_const_v<T> && !std::is_reference_v<T> && HasBaseClass_v<T>>>
{
    using Type = typename T::EntropySuper;
};

template <typename T>
struct BaseClassWithQualifiersOf<const T, std::enable_if_t<HasBaseClass_v<T>>>
{
    using Type = const typename BaseClassWithQualifiersOf<std::remove_const_t<T>>::Type;
};

template <typename T>
struct BaseClassWithQualifiersOf<T&, std::enable_if_t<HasBaseClass_v<T>>>
{
    using Type = typename BaseClassWithQualifiersOf<std::remove_reference_t<T>>::Type&;
};

template <class T>
using BaseClassOf_t = typename BaseClassOf<T>::Type;

template <class T>
using BaseClassWithQualifiersOf_t = typename BaseClassWithQualifiersOf<T>::Type;

//==========================

namespace details
{

template <typename TFunc, typename... TArgs>
class IsInvocableImpl
{
    template <typename UFunc, typename... UArgs>
    static auto CanCall(UFunc&& p) -> decltype(p(std::declval<UArgs>()...), std::true_type());
    template <typename, typename...>
    static std::false_type CanCall(...);

    typedef decltype(CanCall<TFunc, TArgs...>(std::declval<TFunc>())) ResultType; // NOLINT

public:
    static constexpr bool value = ResultType::value;
};

} // namespace details

template <typename F, typename... Args>
constexpr bool IsInvocable_v = details::IsInvocableImpl<F, Args...>::value;

//------

namespace details
{

template <typename TClass, typename TMethod, typename... TArgs>
class IsClassMethodInvocableImpl
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

} // namespace details

template <typename C, typename M, typename... Args>
constexpr bool IsClassMethodInvocableImpl_v = details::IsClassMethodInvocableImpl<C, M, Args...>::value;

//==========================

// Turns a type like "const T*&" into simply "T".

template <typename T, typename = void>
struct UnqualifiedType
{
    using Type = T;
};

template <typename T>
struct UnqualifiedType<T, std::enable_if_t<std::is_const_v<T> || std::is_pointer_v<T> || std::is_reference_v<T> ||
                                           std::is_rvalue_reference_v<T>>>
{
    using Type = typename UnqualifiedType<std::remove_const_t<std::remove_pointer_t<std::remove_reference_t<T>>>>::Type;
};

template <typename T>
using UnqualifiedType_t = typename UnqualifiedType<T>::Type;

} // namespace Traits

} // namespace Entropy
