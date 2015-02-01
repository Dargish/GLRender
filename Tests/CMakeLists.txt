set(TARGET tests)

file(GLOB_RECURSE SRC *.cpp)
file(GLOB_RECURSE HDR "src/*.h")

include_directories(${JSON_INCLUDE_DIR})
include_directories(${BOOST_INCLUDE_DIR})

add_executable(${TARGET} ${SRC} ${HDR})

target_link_libraries(${TARGET} glrender)

target_lib_boost_libs(${TARGET} serialization)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Projects")

configure_file(${TARGET}.vcxproj.user ${TARGET}.vcxproj.user COPYONLY)

ADD_SOURCE_GROUP(${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${TARGET}
	RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)