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

#define ENTROPY_LITERAL(...) __VA_ARGS__
