include_directories(. .. ../DB ../Role ../Protocol
                    ../../library/openssl/include
                    ../../library/MySql/include
                    ../../library/tinyxml
                    ../../library/luabind
                    ../../library/lua
                    ../../library/libcurl/include/curl
                    ../../library/boost/boost_1_70_0)

link_directories(../DB)

link_libraries(gamecfg)

add_library(tools STATIC
            AES.cpp
            CsvHelper.cpp
            DBConnector.cpp
            FileHelper.cpp
            IFileHelper.cpp
            ILogHelper.cpp
            ITimeHelper.cpp
            LogHelper.cpp
            MD5.cpp
            StringHelper.cpp
            TimeHelper.cpp
            Tools.cpp
            inifile.cpp
            IScheduledHelper.cpp
            ScheduledHelper.cpp
            MsgCostStat.cpp
            fcaseopen.c
            ../ObjID.cpp)
