#pragma once

class ErrorReporter
{
public:
    enum class Type {
        Undefined               = 0,
        ServiceStartingError    = 1,
        RunningError            = 2
    };

public:
    void            SetGameID(uint32_t gameID) { mGameID = gameID; }
    void            SetServerID(uint32_t serverID) { mServerID = serverID; }
    void            SetType(Type type) { mType = type; }
    void            SetMsg(std::string msg) { mMsg = std::move(msg); }
    void            SetURL(std::string url) { mURL = std::move(url); }

    void            Report(bool useThread);

private:
    std::string     ComposePostData();

private:
    uint32_t        mGameID     = 0;
    uint32_t        mServerID   = 0;
    Type            mType       = Type::Undefined;
    std::string     mMsg;
    std::string     mURL;
};