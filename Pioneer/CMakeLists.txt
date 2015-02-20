if(MSVC)
  set(VCXPROJ_FILE ${CMAKE_CURRENT_SOURCE_DIR}/pioneer.vcxproj.user)
endif()

set(TARGET Pioneer)

file(GLOB_RECURSE HDR src/*.cpp)
file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${TARGET} ${SRC} ${HDR})

target_link_libraries(${TARGET} GLRender)

if(MSVC)
	set_property(TARGET ${TARGET} PROPERTY FOLDER "Binaries")
	add_source_group(${CMAKE_CURRENT_SOURCE_DIR})
	configure_file(${VCXPROJ_FILE} ${TARGET}.vcxproj.user COPYONLY)
endif()

install(TARGETS ${TARGET} RUNTIME DESTINATION bin)