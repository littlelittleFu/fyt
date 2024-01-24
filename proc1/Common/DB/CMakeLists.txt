include_directories(. .. ../Protocol ../Role ../Tools)

aux_source_directory(. DBSRCS)

add_library(gamecfg STATIC ${DBSRCS})
