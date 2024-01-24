include_directories(.
                    ../Common
                    ../Common/Protocol
                    ../Common/Tools
                    ../Common/Lua
                    ../Common/Role
                    ../Common/DB
                    ../Common/FlatBuffers
                    ../library
                    ../library/libcurl/include/curl
                    ../library/json/json
                    ../library/openssl/include
                    ../library/NetLib
                    ../library/NetLib/linux
                    ../library/lua
                    ../library/luabind
                    ../library/boost/boost_1_70_0
                    ../library/flatbuffers/include
                    ../library/tinyxml)

link_directories(${CMAKE_BINARY_DIR}/Common/Protocol
                 ${CMAKE_BINARY_DIR}/Common/Tools
                 ${CMAKE_BINARY_DIR}/Common/DB
                 ${CMAKE_BINARY_DIR}/library/lua
                 ${CMAKE_BINARY_DIR}/library/luabind
                 ${CMAKE_BINARY_DIR}/library/NetLib
                 ${CMAKE_BINARY_DIR}/library/tinyxml
                 ${CMAKE_BINARY_DIR}/library/json
                 ../library/libcurl/lib
                 ../library/zlib/prebuilt
                 ../library/openssl/lib)

link_libraries(NetLib proto gamecfg tools curl ssl crypto json lua luabind tinyxml z pthread dl)

aux_source_directory(. CS_SRCS)
aux_source_directory(../Common/Lua LUA_SRCS)

add_executable(CenterServer ${CS_SRCS} ${LUA_SRCS})
