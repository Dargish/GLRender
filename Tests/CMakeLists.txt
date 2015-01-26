set(TARGET tests)

file(GLOB_RECURSE SRC *.cpp)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} glrender)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Projects")

# configure_file(${TARGET}.vcxproj.user ${TARGET}.vcxproj.user COPYONLY)

install(TARGETS ${TARGET}
	RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)