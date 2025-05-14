// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#include "Entropy/Core/Log.h"
#include <array>
#include <iostream>
#include <sstream>

#ifdef ENTROPY_WINDOWS
#undef ARRAYSIZE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef GetClassName
#endif

namespace Entropy
{

namespace details
{

/// <remarks>
/// We use the base STL because this is a "low-level" component and we want to avoid circular re-entrancy when things
/// fail
/// </remarks>
class LogBuffer : public std::stringbuf
{
    typedef std::stringbuf Super;

public:
    LogBuffer(LogLevel level)
        : _level(level)
    {
    }

    virtual int sync() override
    {
        std::string s    = str();
        size_t delimiter = s.rfind(details::LogMessageDelimiter::delimiter);
        if (delimiter != std::string::npos)
        {
            if (delimiter < s.length() - 1)
            {
                s = s.substr(0, delimiter);
            }
            Log::Write(_level, s.c_str());

            str("");
        }

        return 0;
    }

private:
    LogLevel _level;
};

class LogOStream : public std::ostream
{
public:
    LogOStream(LogLevel level)
        : _buffer(level)
        , std::ostream(&_buffer)
    {
    }

private:
    LogBuffer _buffer;
};

std::array<LogOStream*, static_cast<std::size_t>(LogLevel::Count)>& GetLogStreams()
{
    static LogOStream s0((LogLevel)0);
    static LogOStream s1((LogLevel)1);
    static LogOStream s2((LogLevel)2);
    static LogOStream s3((LogLevel)3);

    static std::array<LogOStream*, static_cast<std::size_t>(LogLevel::Count)> streams({&s0, &s1, &s2, &s3});
    return streams;
}

const char* ToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Debug:
        return "Debug";

    case LogLevel::Info:
        return "Info";

    case LogLevel::Warning:
        return "Warning";

    case LogLevel::Error:
        return "Error";

    case LogLevel::Count:
        break;
    }
    return "";
}

} // namespace details

std::ostream* Log::GetStream(LogLevel level)
{
    if (ENTROPY_UNLIKELY((int)level < 0 || (int)level >= (int)LogLevel::Count))
    {
        return nullptr;
    }

    return details::GetLogStreams()[(int)level];
}

void Log::Write(LogLevel level, const char* msg)
{
    std::cout << "[" << details::ToString(level) << "] " << msg << std::endl;

#ifdef ENTROPY_WINDOWS
    std::stringstream ss;
    ss << "[" << details::ToString(level) << "] " << msg << "\r\n";
    OutputDebugString(ss.str().c_str());
#endif
}

} // namespace Entropy
