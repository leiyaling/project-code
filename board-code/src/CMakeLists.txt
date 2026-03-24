project(board
LANGUAGES CXX C
)

# 查找源文件
file(GLOB_RECURSE SRCS
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.hpp
)

# 查找依赖库
# find_package(nlohmann_json 3.2.0 REQUIRED)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${REDEDA_DEV_DIST_DIR}")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${REDEDA_DEV_DIST_DIR}")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${REDEDA_DEV_DIST_DIR}")

set(TARGET_NAME "rededa_${PROJECT_NAME}")
# 动态库
add_library(${TARGET_NAME} SHARED ${SRCS})

# 添加编译宏定义
target_compile_definitions(${TARGET_NAME} PRIVATE
  REDEDA_${MODEL_NAME_UPPER}_EXPORTS
)

# 添加编译选项
target_compile_options(${TARGET_NAME} PRIVATE
  #-std=c++17
  -fPIC
  -Wall
  -Wextra
  # -Werror
  -Wno-unused-parameter
  -Wno-unused-result

)

message(STATUS "rededa include dir: ${REDEDA_DEV_DIST_DIR}/rededa/include")
# 添加头文件目录
target_include_directories(
  ${TARGET_NAME} PUBLIC
  ${CMAKE_SOURCE_DIR}/inc
  ${REDEDA_DEV_DIST_DIR}/rededa/include
  ${REDEDA_DEV_DIST_DIR}/rededa/include/rededa
  ${REDEDA_DEV_DIST_DIR}/rededa/3rd/include

)

# 添加依赖库目录
target_link_directories(
  ${TARGET_NAME} PUBLIC
  ${REDEDA_DEV_DIST_DIR}

)

# 添加依赖库
target_link_libraries(
  ${TARGET_NAME} PUBLIC

  #nlohmann_json::nlohmann_json
  rededa_logging
  pthread
  project_manager
  rededa_intergfx
  rededa_renderer
  rededa_item_holder
  rededa_layer_manager
  rededa_commonfsm
  rededa_baseoperate
  rededa_drawing
  rededa_selection
  rededa_settings
  rededa_shape
  rededa_shape_fsm
)
set_target_properties(${TARGET_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}
)
install(TARGETS ${TARGET_NAME}
    ARCHIVE DESTINATION ${OUTPUT_DIRECTORY}
    LIBRARY DESTINATION ${OUTPUT_DIRECTORY}
    RUNTIME DESTINATION ${OUTPUT_DIRECTORY}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/inc/ DESTINATION ${OUTPUT_DIRECTORY}/rededa/include)