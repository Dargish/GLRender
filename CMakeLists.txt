cmake_minimum_required (VERSION 3.0)
project(GLRender)


##########
# Global Options
##########

if(CMAKE_COMPILER_IS_GNUCXX)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
elseif(MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /wd4201")
endif()
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


##########
# Dependencies directory
##########

if(NOT DEFINED DEPENDENCIES_DIR)
	set(DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../GLRenderDependencies")
endif()


##########
# GLM
##########

if(NOT DEFINED GLM_VERSION)
	set(GLM_VERSION 0.9.6.1)
endif()
set(GLM_INCLUDE_DIR "${DEPENDENCIES_DIR}/glm/glm-${GLM_VERSION}/")
include_directories(${GLM_INCLUDE_DIR})  # Everything will need glm included as it's public


##########
# JSON
##########

if(NOT DEFINED JSON_VERSION)
  set(JSON_VERSION 1.3.0)
endif()
set(JSON_INCLUDE_DIR "${DEPENDENCIES_DIR}/jsoncpp/jsoncpp-${JSON_VERSION}/include/")
set(JSON_LIB_DIR "${DEPENDENCIES_DIR}/jsoncpp/jsoncpp-${JSON_VERSION}/lib/")


##########
# GLRender include directory
##########

set(GLRENDER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLRender/include")
include_directories(${GLRENDER_INCLUDE_DIR})  # Everything will need glrender


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


##########
# Include projects
##########

add_subdirectory(GLRender)
add_subdirectory(Tests)