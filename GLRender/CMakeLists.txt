set(TARGET glrender)

file(GLOB_RECURSE HDR "include/*.h")
file(GLOB_RECURSE PVT_HDR "src/*.h")
file(GLOB_RECURSE SRC "src/*.cpp")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_definitions(-DGLRENDER_EXPORT)

add_library(${TARGET} SHARED ${SRC} ${HDR} ${PVT_HDR})

if (BOOST_FOUND)
  include_directories(${BOOST_INCLUDE_DIRS})
  target_link_libraries(${TARGET} ${BOOST_LIBRARIES})
endif()

set_property(TARGET ${TARGET} PROPERTY FOLDER "Projects")
ADD_SOURCE_GROUP(${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${TARGET} LIBRARY DESTINATION lib)
install(DIRECTORY "include" DESTINATION include)