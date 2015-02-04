cmake_minimum_required (VERSION 3.0)
project(GLRender)

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

find_package(PkgConfig REQUIRED)

set(GLRENDER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLRender/include")
include_directories(${GLRENDER_INCLUDE_DIR})  # Everything will need glrender

set(GLM_INCLUDE_DIRS ${GLM_ROOT}/include)
include_directories(${GLM_INCLUDE_DIRS})  # Everything will need glm


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

function(TARGET_USE_DEPENDENCIES TARGET_NAME)
  set(DEPENDENCY_NAMES ${ARGN})
  foreach(PKG_CONFIG_NAME IN ITEMS ${DEPENDENCY_NAMES})
    set(_THE_PKG PKG_CONFIG_${PKG_CONFIG_NAME})
    pkg_check_modules(${_THE_PKG} QUIET ${PKG_CONFIG_NAME})
    if(${${_THE_PKG}_FOUND})
      message(STATUS "Using ${PKG_CONFIG_NAME} (via pkg-config), version ${${_THE_PKG}_VERSION}")

      if(${_THE_PKG}_INCLUDE_DIRS)
        target_include_directories(${TARGET_NAME} SYSTEM PUBLIC ${${_THE_PKG}_INCLUDE_DIRS})
      endif()

      if(${_THE_PKG}_LIBRARY_DIRS)
        foreach(LIB_DIR IN ITEMS ${${_THE_PKG}_LIBRARY_DIRS})
          foreach(LIB_NAME IN ITEMS ${${_THE_PKG}_LIBRARIES})
            set(LIB "${LIB_DIR}/lib${LIB_NAME}.so")
            if(EXISTS ${LIB})
              target_link_libraries(${TARGET_NAME} ${LIB})
            endif()
          endforeach()
        endforeach()
      else()
        foreach(LIB_NAME IN ITEMS ${${_THE_PKG}_LIBRARIES})
          target_link_libraries(${TARGET_NAME} ${LIB_NAME})
        endforeach()
      endif()
    else()
      message(STATUS "No package config found, linking directly to ${PKG_CONFIG_NAME}")
      target_link_libraries(${TARGET_NAME} ${PKG_CONFIG_NAME})
    endif()
  endforeach()
endfunction()


##########
# Include projects
##########

# add_subdirectory(GLRender)
add_subdirectory(Tests)