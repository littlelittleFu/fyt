#pragma once

#include <random>

#define CopyArray(dst, src) memcpy_s(dst, sizeof(dst), src, sizeof(src))
#define ZeroArray(ary) memset(ary, 0, sizeof(ary))

namespace Tools {

    char * ConvertIntToIP(uint32_t ip);

    std::string GenerateGuidString();

    uint32_t MakeDWORD(uint16_t high, uint16_t low);

    uint16_t HighWORD(uint32_t dw);

    uint16_t LowWORD(uint32_t dw);

    uint64_t MakeQWORD(uint32_t high, uint32_t low);

    uint32_t GenerateUINT32();

    uint64_t GenerateUINT64();

    bool IsContainIllegalCharacters(const char* ch);

    template<class T>
    T GenerateRandomInteger(T lower, T upper)
    {
        static auto engine = std::default_random_engine{std::random_device{}()};
        if (lower > upper) std::swap(lower, upper);
        auto dist = std::uniform_int_distribution<T>{lower, upper};
        return dist(engine);
    }

    inline bool HaveChance(uint32_t nPercent) { return GenerateRandomInteger<uint16_t>(0, 99) < nPercent; }

    inline bool HaveChance10T(uint32_t chance) { return GenerateRandomInteger<uint16_t>(0, 9999) < chance; }

    void GetRelativePos(uint16_t seq, int16_t &dx, int16_t &dy);

    template<class T>
    void Purge(T &data)
    {
        T().swap(data);
    }

    std::string & AppendPathSeperator(std::string &path);
}
