include_directories(../Common
                    ../Common/Protocol
                    ../Common/Tools
                    ../library
                    ../library/openssl/include
                    ../library/libcurl/include/curl
                    ../library/json/json
                    ../library/NetLib
                    ../library/NetLib/linux)

link_directories(${CMAKE_BINARY_DIR}/Common/Protocol
                 ${CMAKE_BINARY_DIR}/Common/Tools
                 ${CMAKE_BINARY_DIR}/library/NetLib
                 ${CMAKE_BINARY_DIR}/library/json
                 ../library/libcurl/lib
                 ../library/zlib/prebuilt
                 ../library/openssl/lib)

link_libraries(NetLib proto tools curl ssl crypto
               json z pthread dl)

aux_source_directory(. LS_SRCS)

add_executable(LoginServer ${LS_SRCS})
