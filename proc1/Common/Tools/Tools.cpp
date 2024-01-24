#include "stdafx.h"
#include "Tools.h"

#include <chrono>
#include <cstdlib>
#include <regex>

#ifdef _WIN32
#include <winsock.h>
#include <objbase.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "sole.hpp"
#endif

namespace Tools
{
    char * ConvertIntToIP(uint32_t ip)
    {
        in_addr addr;
        addr.s_addr = ip;
        return inet_ntoa(addr);
    }

    std::string GenerateGuidString()
    {
#ifdef _WIN32
        char cBuffer[64] = { 0 };
        GUID guid;
        CoCreateGuid(&guid);
        sprintf_s(cBuffer, sizeof(cBuffer),
            "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
            guid.Data1, guid.Data2,
            guid.Data3, guid.Data4[0],
            guid.Data4[1], guid.Data4[2],
            guid.Data4[3], guid.Data4[4],
            guid.Data4[5], guid.Data4[6],
            guid.Data4[7]);
        return cBuffer;
#else
        auto uuid = sole::uuid4();
        auto str = uuid.str();
        return trans_toupper(str);
#endif
    }

    uint32_t MakeDWORD(uint16_t high, uint16_t low)
    {
        return high << 16 | low;
    }

    uint16_t HighWORD(uint32_t dw)
    {
        return uint16_t(dw >> 16);
    }

    uint16_t LowWORD(uint32_t dw)
    {
        return uint16_t(dw & 0xFFFF);
    }

    uint64_t MakeQWORD(uint32_t high, uint32_t low)
    {
        return uint64_t(high) << 32 | low;
    }

    uint32_t GenerateUINT32()
    {
        static uint32_t i = 0;

        if (i == 0) {
            i = GenerateRandomInteger<uint32_t>(1, UINT32_MAX);
            return i;
        }

        if (i == UINT32_MAX) i = 0;

        return ++i;
    }

    uint64_t GenerateUINT64()
    {
        using std::chrono::duration_cast;
        using std::chrono::milliseconds;
        using std::chrono::system_clock;

        auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        static uint16_t inc = 0;
        ++inc;

        return (millisec_since_epoch << 16 | inc);
    }

    bool IsContainIllegalCharacters(const char* ch)
    {
        if (!ch) return false;

        auto *cfg = DATA::IllegalCharactersConfig::Instance();
        if (!cfg) return false;

        const auto &list = cfg->GetData();
        if (list.empty()) return false;

        for (const auto& i : list) {
            try {
                if (std::regex_search(ch, std::regex(i->characters.c_str())))return true;
            }
            catch(...){
                LOG_ERROR("Tools:invalid regular expression ! str is %s",i->characters.c_str());
            }
        }
        return false;
    }

    void GetRelativePos(uint16_t seq, int16_t &dx, int16_t &dy)
    {
        if (seq == 0) { dx = 0; dy = 0; return; }

        auto square = [](uint16_t x) { return x * x; };

        uint16_t n = 1;

        while (seq >= square(2 * n + 1)) ++n;

        auto len = 2 * n + 1;

        auto lt = square(2 * n - 1);
        auto rt = lt + len - 1;
        auto rb = rt + len - 1;
        auto lb = rb + len - 1;

        if (seq < rt) {
            dx = seq - (lt + n);
            dy = -n;
        }
        else if (seq < rb) {
            dx = n;
            dy = seq - (rt + n);
        }
        else if (seq < lb) {
            dx = rb + n - seq;
            dy = n;
        }
        else {
            dx = -n;
            dy = lb + n - seq;
        }
    }

    std::string & AppendPathSeperator(std::string &path)
    {
        char c = path.empty() ? 0 : path.back();

#ifdef _WIN32
        if (c != '\\' && c != '/') path.append("\\");
#else
        if (c != '/') path.append("/");
#endif
        return path;
    }
}
