aux_source_directory(src LUABIND_SRCS)

include_directories(. ../lua ../boost/boost_1_70_0)

add_library(luabind STATIC ${LUABIND_SRCS})
