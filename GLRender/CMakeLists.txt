set(TARGET GLRender)

add_definitions(-DGLRENDER_EXPORT)

file(GLOB_RECURSE HDR "include/*.h")
file(GLOB_RECURSE PVT_HDR "src/*.h")
file(GLOB_RECURSE SRC "src/*.cpp")

add_library(${TARGET} SHARED ${SRC} ${HDR} ${PVT_HDR})

target_include_directories(${TARGET} PUBLIC "${GLRENDER_SRC_DIR}")

if(MSVC)
	target_link_library(${TARGET} libboost_serialization-vc120-mt-1_57.lib libboost_serialization-vc120-mt-gd-1_57.lib)
	target_link_library(${TARGET} sfml-graphics.lib sfml-graphics-d.lib)
	target_link_library(${TARGET} sfml-window.lib sfml-window-d.lib)
	target_link_library(${TARGET} sfml-system.lib sfml-system-d.lib)
	target_link_library(${TARGET} glew32.lib glew32.lib)
else()
	target_link_libraries(${TARGET} boost_serialization sfml-graphics sfml-window sfml-system glew32)
endif()

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
	DIRECTORY include
	DESTINATION ${CMAKE_INSTALL_PREFIX}
	)