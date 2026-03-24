cmake_minimum_required(VERSION 3.20)

set(MODEL_NAME "board")
set(MODEL_NAME_UPPER "BOARD")

project(${MODEL_NAME}
VERSION 0.3.1
LANGUAGES C CXX
)


# 获取DEV_DIST环境变量路径
set(REDEDA_DEV_DIST_DIR $ENV{REDEDA_PLUS_DEV_DIST})
message(STATUS ${REDEDA_DEV_DIST_DIR})
# 替换反斜杠为正斜杠
string(REPLACE  "\\"  "/"  REDEDA_DEV_DIST_DIR  ${REDEDA_DEV_DIST_DIR})

set(OUTPUT_DIRECTORY ${REDEDA_DEV_DIST_DIR})

configure_file(${CMAKE_SOURCE_DIR}/src/version.h.in ${CMAKE_SOURCE_DIR}/inc/rededa/${MODEL_NAME}/version.h)
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (call a build directory) and run cmake from there.
")
endif()
# set global variables



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH ${REDEDA_DEV_DIST_DIR}/rededa/3rd/cmake ${CMAKE_MODULE_PATH})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_TYPE_Debug "Debug")
set(BUILD_TYPE_Release "Release")

message(STATUS "cmake module path: ${CMAKE_MOUDLE_PATH}")

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE ${BUILD_TYPE_RELEASE})
endif()
message(STATUS "build type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE STREQUAL BUILD_TYPE_Debug)
  set(CMAKE_VERBOSE_MAKEFILE ON)
  add_definitions(-DDEBUG)
endif()


# find packages
# find_package(spdlog REQUIRED)
# find_package(fmt REQUIRED)

# add sub directory
add_subdirectory(src)

# testing
option(BUILD_TESTING "build tests" ON)
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  message(STATUS "enable testing")
  enable_testing()
  find_package(GTest REQUIRED)
  include(GoogleTest)
  add_subdirectory(test)
endif()
