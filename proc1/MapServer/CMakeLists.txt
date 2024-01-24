include_directories(.
                    ../Common
                    ../Common/DB
                    ../Common/Item
                    ../Common/Lua
                    ../Common/Map
                    ../Common/PropExp
                    ../Common/Protocol
                    ../Common/Role
                    ../Common/Tools
                    ../library
                    ../library/boost/boost_1_70_0
                    ../library/json
                    ../library/lua
                    ../library/luabind
                    ../library/NetLib
                    ../library/NetLib/linux
                    ../library/openssl/include
                    ../library/tinyxml
                    ../library/zlib/include)

link_directories(${CMAKE_BINARY_DIR}/Common/Protocol
                 ${CMAKE_BINARY_DIR}/Common/Tools
                 ${CMAKE_BINARY_DIR}/Common/DB
                 ${CMAKE_BINARY_DIR}/library/json
                 ${CMAKE_BINARY_DIR}/library/lua
                 ${CMAKE_BINARY_DIR}/library/luabind
                 ${CMAKE_BINARY_DIR}/library/NetLib
                 ${CMAKE_BINARY_DIR}/library/tinyxml
                 ../library/openssl/lib
                 ../library/zlib/prebuilt)

link_libraries(NetLib proto gamecfg tools crypto lua luabind json tinyxml z pthread dl)

aux_source_directory(. MS_SRCS)
aux_source_directory(../Common/Item ITEM_SRCS)
aux_source_directory(../Common/Lua LUA2_SRCS)
aux_source_directory(../Common/Map MAP_SRCS)
aux_source_directory(../Common/Role ROLE_SRCS)

add_executable(MapServer ${MS_SRCS} ${ITEM_SRCS} ${LUA2_SRCS} ${MAP_SRCS} ${ROLE_SRCS}
               ../Common/Globle.cpp
               ../Common/IObserver.cpp
               ../Common/ISubject.cpp)
