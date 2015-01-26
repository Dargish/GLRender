set(TARGET glrender)

file(GLOB_RECURSE HDR "include/*.h")
file(GLOB_RECURSE PVT_HDR "src/*.h")
file(GLOB_RECURSE SRC "src/*.cpp")

include_directories(${JSON_INCLUDE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_definitions(-DRENDERER_EXPORT)

add_library(${TARGET} SHARED ${SRC} ${HDR} ${PVT_HDR})

set_property(TARGET ${TARGET} PROPERTY FOLDER "Projects")

target_link_libraries(${TARGET} ${JSON_LIB_DIR}/jsoncpp.lib)

ADD_SOURCE_GROUP(${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${TARGET}
	RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin
	LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib
	ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib/static)

install(DIRECTORY "include" DESTINATION ${PROJECT_BINARY_DIR})