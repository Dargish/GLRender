if(MSVC)
	set(VCXPROJ_FILE ${CMAKE_CURRENT_SOURCE_DIR}/tests.vcxproj.user)
endif()

function(ADD_GLR_TEST TEST_NAME)
	file(GLOB_RECURSE SRC *.cpp)
	file(GLOB_RECURSE HDR *.h)

	add_executable(${TEST_NAME} ${SRC} ${HDR})
	message(STATUS "target_use_dependencies(${TEST_NAME} ${ARGN})")

	if(MSVC)
		set_property(TARGET ${TEST_NAME} PROPERTY FOLDER "Tests")
		add_source_group(${CMAKE_CURRENT_SOURCE_DIR})
		configure_file(${VCXPROJ_FILE} ${TEST_NAME}.vcxproj.user COPYONLY)
	endif()
	target_link_libraries(${TEST_NAME} GLRender)

	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/_build/GLRender/Debug")

	message(STATUS "Added test ${TEST_NAME}")
endfunction()

add_subdirectory(FileArchiveTest)
add_subdirectory(CreateWindowTest)
add_subdirectory(CreateEntityTest)