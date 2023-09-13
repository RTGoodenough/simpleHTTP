cmake_minimum_required(VERSION 3.14)

OPTION(DEBUG_MODE OFF)

set(PROJECT_NAME simpleHTTP)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(SRC_DIR src)
set(DEPS_DIR deps)
set(INCLUDE_DIR includes)

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

add_subdirectory(${DEPS_DIR}/party_llama)
add_subdirectory(${DEPS_DIR}/pirate)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  pirate
  party_llama
)

if (DEBUG_MODE)
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")
else()
  set(CMAKE_BUILD_TYPE Release)
endif()

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./../)