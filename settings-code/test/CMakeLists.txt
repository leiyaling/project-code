project(rtest_settings
LANGUAGES CXX C
)

# 查找源文件
file(GLOB_RECURSE SRCS
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.hpp
  ${CMAKE_SOURCE_DIR}/test/*.cpp
)

# 查找依赖库
# find_package(nlohmann_json 3.2.0 REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${REDEDA_DEV_DIST_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${REDEDA_DEV_DIST_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${REDEDA_DEV_DIST_DIR}")


add_executable(${PROJECT_NAME}  ${SRCS})

# 添加编译宏定义
target_compile_definitions(${PROJECT_NAME} PRIVATE
  REDEDA_SETTINGS_EXPORTS
)

# 添加编译选项
target_compile_options(${PROJECT_NAME} PRIVATE
  #-std=c++17

  -Wall
  -Wextra
  -Werror
  -Wno-unused-parameter
  -Wno-unused-result

)
if(CODE_COVERAGE)
  message(STATUS "code coverage")
  target_compile_options(${PROJECT_NAME} PRIVATE
    --coverage
  )

  target_link_options(${PROJECT_NAME} PRIVATE
    --coverage
  )
endif()

# 添加头文件目录
target_include_directories(
  ${PROJECT_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/inc
  ${CMAKE_SOURCE_DIR}/src
  ${REDEDA_DEV_DIST_DIR}/rededa/include/rededa
  ${REDEDA_DEV_DIST_DIR}/rededa/3rd/include

)

# 添加依赖库目录
target_link_directories(
  ${PROJECT_NAME} PUBLIC
  ${REDEDA_DEV_DIST_DIR}
)

# 添加依赖库
target_link_libraries(
  ${PROJECT_NAME} PUBLIC

#  nlohmann_json::nlohmann_json
  GTest::gtest
  GTest::gtest_main
  rededa_logging
  #fmt
  pthread
)
