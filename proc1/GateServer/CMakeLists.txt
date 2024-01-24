include_directories(../Common
                    ../Common/Protocol
                    ../Common/Tools
                    ../library
                    ../library/openssl/include
                    ../library/NetLib
                    ../library/NetLib/linux)

link_directories(${CMAKE_BINARY_DIR}/Common/Protocol
                 ${CMAKE_BINARY_DIR}/Common/Tools
                 ${CMAKE_BINARY_DIR}/library/NetLib
                 ../library/openssl/lib)

link_libraries(NetLib proto tools crypto pthread dl)

aux_source_directory(. GS_SRCS)

add_executable(GateServer ${GS_SRCS})
