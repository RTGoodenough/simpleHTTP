cmake_minimum_required(VERSION 3.16)
SET(PROJECT_NAME simpleHTTP)
project(${PROJECT_NAME})
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(INCLUDE_DIR includes)
SET(SRC_DIR src)
SET(VENDOR_DIR vendor)

add_library(
  ${PROJECT_NAME}
  SHARED
)

add_subdirectory(${SRC_DIR})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${INCLUDE_DIR}
)

add_subdirectory(${VENDOR_DIR}/spdlog)
target_link_libraries(
  ${PROJECT_NAME}
  spdlog
)

include_directories(
  SYSTEM
  ${VENDOR_DIR}/spdlog/include
)