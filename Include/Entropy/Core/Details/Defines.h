// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

#include <type_traits>

#ifndef ENTROPY_CONSTEXPR
#if __cplusplus >= 201703L
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

#define ENTROPY_LITERAL(...) __VA_ARGS__

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
