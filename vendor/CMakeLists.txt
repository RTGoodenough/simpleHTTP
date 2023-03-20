cmake_minimum_required(VERSION 3.14)

Set(LIB_NAME VENDOR)
project(${LIB_NAME})

add_subdirectory(spdlog)

add_library(${LIB_NAME} INTERFACE)

target_link_libraries(
  ${LIB_NAME}
  INTERFACE
  spdlog::spdlog
)