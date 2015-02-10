include_directories("${GLRENDER_SRC_DIR}")

add_glr_test(FileArchiveTest)

target_link_library(FileArchiveTest libboost_serialization-vc120-mt-1_57.lib libboost_serialization-vc120-mt-gd-1_57.lib)
