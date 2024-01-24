aux_source_directory(. JSON_SRCS)
include_directories(.)
add_library(json STATIC ${JSON_SRCS})
