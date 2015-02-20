cmake_minimum_required (VERSION 3.0)
project(GLRender)
enable_testing()

##########
# Global Options
##########

if(CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
elseif(MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4201 /wd4251")
endif()
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


##########
# Global Dependencies
##########

if(NOT DEFINED DEPENDENCIES_ROOT)
  set(DEPENDENCIES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../GLRenderDependencies")
endif()
set(DEPENDENCIES_INCLUDE_DIR "${DEPENDENCIES_ROOT}/include")
set(DEPENDENCIES_LIB_DIR "${DEPENDENCIES_ROOT}/lib")
include_directories(${DEPENDENCIES_INCLUDE_DIR})

set(GLRENDER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLRender/include")
set(GLRENDER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLRender/src")
include_directories(${GLRENDER_INCLUDE_DIR})  # Everything will need GLRender

##########
# Global helper functions
##########

macro(SUBDIRLIST RESULT CURR_DIR)
  file(GLOB CHILDREN RELATIVE ${CURR_DIR} ${CURR_DIR}/*)
  set(DIRLIST "")
  foreach(CHILD ${CHILDREN})
    if(IS_DIRECTORY ${CURR_DIR}/${CHILD})
      list(APPEND DIRLIST ${CHILD})
    endif()
  endforeach()
  set(${RESULT} ${DIRLIST})
endmacro()

macro(LIST_FILES RESULT CURR_DIR)
  file(GLOB CHILDREN RELATIVE ${CURR_DIR} ${CURR_DIR}/*)
  set(FILELIST "")
  foreach(CHILD ${CHILDREN})
    if(NOT IS_DIRECTORY ${CURR_DIR}/${CHILD})
        list(APPEND FILELIST ${CURR_DIR}/${CHILD})
    endif()
  endforeach()
  set(${RESULT} ${FILELIST})
endmacro()

macro(SOURCE_GROUP_RECURSE BASE_DIR CURR_DIR)
	LIST_FILES(SRC_FILES ${BASE_DIR}${CURR_DIR})
	string(REPLACE "/" "\\\\" SRC_GRP "${CURR_DIR}")
	source_group("${SRC_GRP}" FILES ${SRC_FILES})
	SUBDIRLIST(SUB_DIRS ${BASE_DIR}${CURR_DIR})
	foreach(SUB_DIR ${SUB_DIRS})
		SOURCE_GROUP_RECURSE(${BASE_DIR} ${CURR_DIR}/${SUB_DIR})
	endforeach()
endmacro()

macro(ADD_SOURCE_GROUP CURR_DIR)
	SOURCE_GROUP_RECURSE(${CURR_DIR} "")
endmacro()

function(TARGET_LINK_LIBRARY TARGET LIB_NAME LIBD_NAME)
    get_filename_component(LIB_PATH "${DEPENDENCIES_LIB_DIR}/${LIB_NAME}" REALPATH)
    get_filename_component(LIBD_PATH "${DEPENDENCIES_LIB_DIR}/${LIBD_NAME}" REALPATH)

    if((EXISTS ${LIB_PATH}) AND (EXISTS ${LIBD_PATH}))
      message(STATUS "Linking ${TARGET} to ${LIB_PATH} with debug")
      target_link_libraries(${TARGET} optimized ${LIB_PATH} debug ${LIBD_PATH})
    elseif(EXISTS ${LIB_PATH})
      message(STATUS "Linking ${TARGET} to ${LIB_PATH}")
      target_link_libraries(${TARGET} optimized ${LIB_PATH})
    else()
      message(STATUS "Linking ${TARGET} to ${DEPENDENCY}")
      target_link_libraries(${TARGET} ${DEPENDENCY})
    endif()
endfunction()

##########
# Include projects
##########

add_subdirectory(GLRender)
add_subdirectory(Tests)
add_subdirectory(Pioneer)