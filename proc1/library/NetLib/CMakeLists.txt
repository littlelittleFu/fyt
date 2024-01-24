include_directories(.
                    ..
                    linux
                    ../../Common
                    ../../Common/Tools
                    ../../library/openssl/include)

add_library(NetLib STATIC
            CBufManager.cpp
            CLogger.cpp
            CNetManager.cpp
            Config.cpp
            IProtoMgr.cpp
            ISessionFactory.cpp
            Session.cpp
            SessionManager.cpp
            linux/CConnectCtrl.cpp
            linux/CEpollCtrl.cpp
            linux/CListener.cpp
            linux/CMutex.cpp
            linux/CSocket.cpp
            ../../Common/SessionFactory.cpp)
