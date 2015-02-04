set(TARGET tests)

file(GLOB_RECURSE SRC *.cpp)
file(GLOB_RECURSE HDR "src/*.h")

add_executable(${TARGET} ${SRC} ${HDR})

# target_link_libraries(${TARGET} glrender)

target_use_dependencies(${TARGET} boost_serialization)

set_property(TARGET ${TARGET} PROPERTY FOLDER "Projects")
ADD_SOURCE_GROUP(${CMAKE_CURRENT_SOURCE_DIR})

# Copy vcxproj settings file with instructions on where to run
configure_file(${TARGET}.vcxproj.user ${TARGET}.vcxproj.user COPYONLY)

install(TARGETS ${TARGET}
  RUNTIME DESTINATION bin)