// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

#include <type_traits>

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201103L) || __cplusplus >= 201103L)
#define ENTROPY_CPP11
#else
#define __ENTROPY_STRINGIFY2(x) #x
#define __ENTROPY_STRINGIFY(x) __ENTROPY_STRINGIFY2(x)
#pragma message("C++ 11 is required. Current language version: " __ENTROPY_STRINGIFY(__cplusplus))
#error C++ 11 is required
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201402L) || __cplusplus >= 201402L)
#define ENTROPY_CPP14
#endif

#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#define ENTROPY_CPP17
#endif

#ifndef ENTROPY_CONSTEXPR
#ifdef ENTROPY_CPP17
#define ENTROPY_CONSTEXPR constexpr
#else
#define ENTROPY_CONSTEXPR
#endif
#endif

#if !defined(_MSC_VER) || defined(__clang__)
#define ENTROPY_LIKELY(x) __builtin_expect(!!(x), true)
#define ENTROPY_UNLIKELY(x) __builtin_expect(!!(x), false)
#else
#define ENTROPY_LIKELY(x) (x)
#define ENTROPY_UNLIKELY(x) (x)
#endif

#ifdef _MSC_VER
#define ENTROPY_MSVC
#else
#undef ENTROPY_MSVC
#endif

#ifdef __GNUG__
#define ENTROPY_GCC
#else
#undef ENTROPY_GCC
#endif

#ifdef _DEBUG
#define ENTROPY_DEBUG
#endif

#ifdef ENTROPY_ENABLE_EXPORT
#ifdef SMARTENGINE_WINDOWS
#ifdef ENTROPY_BUILDING_DLL
#define ENTROPY_EXPORT_INTERFACE __declspec(dllexport)
#define ENTROPY_EXPORT_CLASS __declspec(dllexport)
#define ENTROPY_EXPORT_FUNC __declspec(dllexport)
#define ENTROPY_EXPORT_VAR __declspec(dllexport)
#else
#define ENTROPY_EXPORT_INTERFACE __declspec(dllimport)
#define ENTROPY_EXPORT_CLASS __declspec(dllimport)
#define ENTROPY_EXPORT_FUNC __declspec(dllimport)
#define ENTROPY_EXPORT_VAR __declspec(dllimport)
#endif
#elif defined SMARTENGINE_LINUX
#define ENTROPY_EXPORT_INTERFACE __attribute__((visibility("default")))
#define ENTROPY_EXPORT_CLASS __attribute__((visibility("default")))
#define ENTROPY_EXPORT_FUNC __attribute__((visibility("default")))
#define ENTROPY_EXPORT_VAR __attribute__((visibility("default")))
#elif defined ENTROPY_JAVASCRIPT
#include <emscripten.h>
#define ENTROPY_EXPORT_INTERFACE
#define ENTROPY_EXPORT_CLASS
#define ENTROPY_EXPORT_FUNC EMSCRIPTEN_KEEPALIVE
#define ENTROPY_EXPORT_VAR
#else
#define ENTROPY_EXPORT_INTERFACE
#define ENTROPY_EXPORT_CLASS
#define ENTROPY_EXPORT_FUNC
#define ENTROPY_EXPORT_VAR
#endif
#else // ENTROPY_ENABLE_EXPORT
#define ENTROPY_EXPORT_INTERFACE
#define ENTROPY_EXPORT_CLASS
#define ENTROPY_EXPORT_FUNC
#define ENTROPY_EXPORT_VAR
#endif

#define ENTROPY_LITERAL(...) __VA_ARGS__

#ifdef ENTROPY_CPP17
#define ENTROPY_FALLTHROUGH [[fallthrough]];
#else
#define ENTROPY_FALLTHROUGH
#endif

namespace Entropy
{

using int8   = signed char;
using byte   = unsigned char;
using uint8  = byte;
using int16  = short;
using uint16 = unsigned short;
using int32  = int;
using uint32 = unsigned int;
using int64  = long long;
using uint64 = unsigned long long;

} // namespace Entropy
