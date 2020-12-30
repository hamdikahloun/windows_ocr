cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "windows_ocr")
project(${PROJECT_NAME} LANGUAGES CXX)
file(COPY Bin_64
     DESTINATION ${CMAKE_BINARY_DIR}/runner/Debug)
file(COPY Bin_common
     DESTINATION ${CMAKE_BINARY_DIR}/runner/Debug)
file(COPY Bin_64
     DESTINATION ${CMAKE_BINARY_DIR}/runner/Release)
file(COPY Bin_common
     DESTINATION ${CMAKE_BINARY_DIR}/runner/Release)
# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "windows_ocr_plugin")
file(GLOB SOURCES "*.cpp")

add_library(${PLUGIN_NAME} SHARED
  ${SOURCES}
)

apply_standard_settings(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter flutter_wrapper_plugin)

# List of absolute paths to libraries that should be bundled with the plugin
set(windows_ocr_bundled_libraries
  ""
  PARENT_SCOPE
)
