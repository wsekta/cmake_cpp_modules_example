cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")

set(CMAKE_GENERATOR "/usr/bin/ninja")
set(CMAKE_C_COMPILER "clang-16")
set(CMAKE_CXX_COMPILER "clang++-16")

project(modules_test)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        src/main.cpp)

set(MODULES
        src/module_a.cppm
        src/module_b.cppm)

set(EXECUTABLE_NAME modules_test)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)

set(CMAKE_CXX_EXTENSIONS OFF)

string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
        "clang-scan-deps-16"
        " -format=p1689"
        " --"
        " <CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS>"
        " -x c++ <SOURCE> -c -o <OBJECT>"
        " -MT <DYNDEP_FILE>"
        " -MD -MF <DEP_FILE>"
        " > <DYNDEP_FILE>")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "clang")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG "@<MODULE_MAP_FILE>")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem /usr/lib/llvm-16/lib/clang/16/include -Wall -Wextra")

add_library(${EXECUTABLE_NAME}_lib)

target_sources(${EXECUTABLE_NAME}_lib
        PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES ${MODULES})

add_executable(${EXECUTABLE_NAME})

target_sources(${EXECUTABLE_NAME} PRIVATE ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${EXECUTABLE_NAME}_lib)
