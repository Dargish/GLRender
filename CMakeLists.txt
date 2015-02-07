cmake_minimum_required (VERSION 3.0)
project(GLRender)
enable_testing()

##########
# Global Options
##########

if(CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4201 /wd4251")
endif()
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


##########
# Global Dependencies
##########

set(DEPENDENCIES_INCLUDE_DIR "${${GLRENDER_DEPENDENCIES_ROOT}/include}")
set(DEPENDENCIES_LIB_DIR "${${GLRENDER_DEPENDENCIES_ROOT}/lib}")
include_directories(${DEPENDENCIES_INCLUDE_DIR})

set(GLRENDER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLRender/include")
set(GLRENDER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLRender/src")
include_directories(${GLRENDER_INCLUDE_DIR})  # Everything will need GlRender


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

function(TARGET_USE_DEPENDENCIES TARGET)
  set(DEPENDENCIES ${ARGN})
  foreach(DEPENDENCY DEPENDENCIES)
    if(CMAKE_COMPILER_IS_GNUCXX)
      set(DEP_LIB_NAME "lib${DEP_LIB_NAME}.so")
    elseif(MSVC)
      set(DEP_LIB_NAME "lib${DEP_LIB_NAME}.lib")
    endif()
    target_link_library("{$DEPENDENCIES_LIB_DIR}/${DEP_LIB_NAME}")
  endforeach()
endfunction()

##########
# Include projects
##########

add_subdirectory(GLRender)
add_subdirectory(Tests)