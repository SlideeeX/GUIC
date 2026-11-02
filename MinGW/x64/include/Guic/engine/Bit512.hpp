#pragma once
#include <Guic/config/Types.hpp>

namespace guic { namespace engine {

class Bit512
{
    Uint64 bits[8]{};

public:
    constexpr Bit512() = default;

    constexpr Bit512(Uint16 index)
    {
        bits[index / 64] |= Uint64(1) << (index % 64);
    }

    constexpr Bit512 operator~() const
    {
        Bit512 result;

        for (int i = 0; i < 8; i++)
            result.bits[i] = ~bits[i];

        return result;
    }

    constexpr Bit512 operator|(const Bit512& other) const
    {
        Bit512 result;

        for (int i = 0; i < 8; i++) {
            result.bits[i] = bits[i] | other.bits[i];
        }

        return result;
    }

    constexpr Bit512 operator&(const Bit512& other) const
    {
        Bit512 result;

        for (int i = 0; i < 8; i++) {
            result.bits[i] = bits[i] & other.bits[i];
        }

        return result;
    }

    constexpr bool operator==(const Bit512& other) const
    {
        for (int i = 0; i < 8; i++)
        {
            if (bits[i] != other.bits[i]) {
                return false;
            }
        }

        return true;
    }

    constexpr bool operator!=(const Bit512& other) const
    {
        return !(*this == other);
    }

    constexpr bool empty() const
    {
        for (int i = 0; i < 8; i++)
        {
            if (bits[i]) return false;
        }

        return true;
    }

    constexpr bool any() const
    {
        for (int i = 0; i < 8; i++)
        {
            if (bits[i]) return true;
        }

        return false;
    }
};

}}
