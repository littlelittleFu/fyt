include_directories(. .. ../DB ../Role ../Tools ../../library/NetLib)

add_library(proto STATIC
            DataInfo.cpp
            netdata.cpp
            ProtoClient.cpp
            ProtoClient2.cpp
            ProtoClient3.cpp
            ProtoClient7.cpp
            ProtoCS.cpp
            ProtoDB.cpp
            ProtoGS.cpp
            ProtoLog.cpp
            ProtoLS.cpp
            ProtoMgr.cpp
            ProtoMS.cpp
            ProtoSS.cpp)
