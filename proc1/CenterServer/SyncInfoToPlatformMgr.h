#pragma once
#include <string>

class CreateRoleInfoMgr
{
public:
    CreateRoleInfoMgr() = delete;
    ~CreateRoleInfoMgr() = delete;

    static void SendToPlatform(const PLATFORM_CREATE_ROLE_INFO& info);
    static bool ComposeHttpRequest(const PLATFORM_CREATE_ROLE_INFO& info, char* buf, int bufsz);
    static bool GeneratePlatformCreateRoleInfo(uint64_t roleID, uint64_t userID, const std::string& channel, PLATFORM_CREATE_ROLE_INFO& info);
};