project(SYSYF)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g -pedantic")

# add macros to generate ANTLR Cpp code from grammar
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(sysYFParser
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sysyfDriver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SyntaxTree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SyntaxTreePrinter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ErrorReporter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SyntaxTreeChecker.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sysyfParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sysyfScanner.cpp)
