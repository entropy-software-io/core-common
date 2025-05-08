// Copyright (c) Entropy Software LLC
// This file is licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#pragma once

namespace Entropy
{

inline ENTROPY_CONSTEXPR unsigned int StringHash(const char* key, int len, unsigned int seed = 0)
{
    constexpr unsigned int m = 0x5bd1e995;
    constexpr int r          = 24;

    unsigned int h = seed ^ len;

    const char* data = key;

    while (len >= 4)
    {
        unsigned int k = 0;

        k = ((byte)data[0]);
        k |= ((byte)data[1]) << 8;
        k |= ((byte)data[2]) << 16;
        k |= ((byte)data[3]) << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
    case 3:
        h ^= ((byte)data[2]) << 16;
        [[fallthrough]];
    case 2:
        h ^= ((byte)data[1]) << 8;
        [[fallthrough]];
    case 1:
        h ^= ((byte)data[0]);
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

} // namespace Entropy
