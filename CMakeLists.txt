cmake_minimum_required(VERSION 3.16)
SET(PROJECT_NAME simpleHTTP)
project(${PROJECT_NAME})
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

SET(INCLUDE_DIR includes)
SET(SRC_DIR src)
SET(VENDOR_DIR vendor)

add_executable(
  ${PROJECT_NAME}
  ${SRC_DIR}/simpleHTTP.cpp
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

target_compile_options(
  ${PROJECT_NAME} 
  PUBLIC
  -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Werror -Wno-unused
)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./../)