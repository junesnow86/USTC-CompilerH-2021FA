project(demo)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -g -pedantic")

# add macros to generate ANTLR Cpp code from grammar
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(demoParser ${CMAKE_CURRENT_SOURCE_DIR}/grammar/demoParser.yy ${CMAKE_CURRENT_BINARY_DIR}/demoParser.cpp
             COMPILE_FLAGS "-Wall -Wcounterexamples --defines=${CMAKE_CURRENT_BINARY_DIR}/demoParser.h")
FLEX_TARGET(demoScanner ${CMAKE_CURRENT_SOURCE_DIR}/grammar/demoScanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/demoScanner.cpp
            COMPILE_FLAGS "--debug --c++")
ADD_FLEX_BISON_DEPENDENCY(demoScanner demoParser)

# include generated files in project environment
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(demo
  ${CMAKE_CURRENT_SOURCE_DIR}/src/demoDriver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SyntaxTree.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SyntaxTreePrinter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ErrorReporter.cpp
  ${BISON_demoParser_OUTPUTS}
  ${FLEX_demoScanner_OUTPUTS})