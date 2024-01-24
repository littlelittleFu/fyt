include_directories(../Common
                    ../Common/Protocol
                    ../Common/Tools
                    ../library
                    ../library/openssl/include
                    ../library/fmt/include/fmt
                    ../library/NetLib
                    ../library/NetLib/linux
                    ../library/MySql/include
                    ../library/json)

link_directories(${CMAKE_BINARY_DIR}/Common/Protocol
                 ${CMAKE_BINARY_DIR}/Common/Tools
                 ${CMAKE_BINARY_DIR}/library/json
                 ${CMAKE_BINARY_DIR}/library/NetLib
                 ../library/openssl/lib
                 ../library/fmt/lib
                 ../library/MySql/lib)

link_libraries(NetLib proto tools crypto pthread dl mysqlclient json fmt)

aux_source_directory(. LG_SRCS)

add_executable(LogServer ${LG_SRCS})
