set(TARGET GlRender)

add_definitions(-DGLRENDER_EXPORT)

file(GLOB_RECURSE HDR "include/*.h")
file(GLOB_RECURSE PVT_HDR "src/*.h")
file(GLOB_RECURSE SRC "src/*.cpp")

add_library(${TARGET} SHARED ${SRC} ${HDR} ${PVT_HDR})

target_include_directories(${TARGET} PUBLIC "${GLRENDER_SRC_DIR}")

target_use_dependencies(
	${TARGET}
		boost_serialization
	)

if(MSVC)
	set_property(TARGET ${TARGET} PROPERTY FOLDER "Projects")
	ADD_SOURCE_GROUP(${CMAKE_CURRENT_SOURCE_DIR})
endif()

install(
	TARGETS ${TARGET}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	)
install(
	DIRECTORY "include"
	DESTINATION include
	)