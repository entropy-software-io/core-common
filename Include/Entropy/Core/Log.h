// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

#include "Entropy/Core/Details/Defines.h"
#include <ostream>

namespace Entropy
{

enum class LogLevel
{
    /// <summary>
    /// Diagnostic messages
    /// </summary>
    Debug,

    /// <summary>
    /// Informational messages
    /// </summary>
    Info,

    /// <summary>
    /// Warning - recoverable error
    /// </summary>
    Warning,

    /// <summary>
    /// Unrecoverable error
    /// </summary>
    Error,

    Count
};

class Log
{
public:
    static ENTROPY_EXPORT_FUNC std::ostream* GetStream(LogLevel level);
    static ENTROPY_EXPORT_FUNC void Write(LogLevel level, const char* msg);
};

namespace details
{
struct LogMessageDelimiter
{
    static constexpr const char* delimiter = "!EOM!";

    friend std::ostream& operator<<(std::ostream& output, const LogMessageDelimiter& m)
    {
        output << delimiter;
        output.flush();
        return output;
    }
};
} // namespace details

} // namespace Entropy

#define ENTROPY_LOG(Level, msg)                                                                                        \
    {                                                                                                                  \
        auto* __o = ::Entropy::Log::GetStream(::Entropy::LogLevel::Level);                                             \
        if (__o)                                                                                                       \
        {                                                                                                              \
            (*__o) << ::Entropy::Traits::TypeNameOf<                                                                   \
                          typename std::remove_const<typename std::remove_pointer<decltype(this)>::type>::type>{}()    \
                   << "::" << __func__ << "(" << __LINE__ << ") - " << msg                                             \
                   << ::Entropy::details::LogMessageDelimiter();                                                       \
        }                                                                                                              \
    }

#define ENTROPY_LOG_FUNC(Level, msg)                                                                                   \
    {                                                                                                                  \
        auto* __o = ::Entropy::Log::GetStream(::Entropy::LogLevel::Level);                                             \
        if (__o)                                                                                                       \
        {                                                                                                              \
            (*__o) << __func__ << "(" << __LINE__ << ") - " << msg << ::Entropy::details::LogMessageDelimiter();       \
        }                                                                                                              \
    }

#define ENTROPY_LOG_ERROR(msg) ENTROPY_LOG(Error, msg)
#define ENTROPY_LOG_ERROR_FUNC(msg) ENTROPY_LOG_FUNC(Error, msg)

#define ENTROPY_LOG_WARNING(msg) ENTROPY_LOG(Warning, msg)
#define ENTROPY_LOG_WARNING_FUNC(msg) ENTROPY_LOG_FUNC(Warning, msg)

#define ENTROPY_LOG_INFO(msg) ENTROPY_LOG(Info, msg)
#define ENTROPY_LOG_INFO_FUNC(msg) ENTROPY_LOG_FUNC(Info, msg)

#define ENTROPY_CHECK_RETURN(x, msg)                                                                                   \
    if (ENTROPY_UNLIKELY(!(x)))                                                                                        \
    {                                                                                                                  \
        ENTROPY_LOG_ERROR(msg);                                                                                        \
        return;                                                                                                        \
    }

#define ENTROPY_CHECK_RETURN_FUNC(x, msg)                                                                              \
    if (ENTROPY_UNLIKELY(!(x)))                                                                                        \
    {                                                                                                                  \
        ENTROPY_LOG_ERROR_FUNC(msg);                                                                                   \
        return;                                                                                                        \
    }

#define ENTROPY_CHECK_RETURN_VAL(x, r, msg)                                                                            \
    if (ENTROPY_UNLIKELY(!(x)))                                                                                        \
    {                                                                                                                  \
        ENTROPY_LOG_ERROR(msg);                                                                                        \
        return r;                                                                                                      \
    }

#define ENTROPY_CHECK_RETURN_VAL_FUNC(x, r, msg)                                                                       \
    if (ENTROPY_UNLIKELY(!(x)))                                                                                        \
    {                                                                                                                  \
        ENTROPY_LOG_ERROR_FUNC(msg);                                                                                   \
        return r;                                                                                                      \
    }

#ifdef ENTROPY_DEBUG
#include <cassert>

#ifndef ENTROPY_ASSERT
#define ENTROPY_ASSERT(...)                                                                                            \
    if (ENTROPY_UNLIKELY(!(__VA_ARGS__)))                                                                              \
    {                                                                                                                  \
        ENTROPY_LOG_ERROR_FUNC("Assertion failed: " << #__VA_ARGS__);                                                  \
        assert(false);                                                                                                 \
    }
#endif

#ifndef ENTROPY_ASSERT_MSG
#define ENTROPY_ASSERT_MSG(x, msg)                                                                                     \
    if (ENTROPY_UNLIKELY(!(x)))                                                                                        \
    {                                                                                                                  \
        ENTROPY_LOG_ERROR_FUNC("Assertion failed: " << msg);                                                           \
        assert(false);                                                                                                 \
    }
#endif
#else
#ifndef ENTROPY_ASSERT
#define ENTROPY_ASSERT(x)
#endif
#ifndef ENTROPY_ASSERT_MSG
#define ENTROPY_ASSERT_MSG(x, msg)
#endif
#endif
#ifndef ENTROPY_ASSERT_NOT_IMPLEMENTED
#define ENTROPY_ASSERT_NOT_IMPLEMENTED() ENTROPY_ASSERT_MSG(false, "Not implemented.")
#endif
