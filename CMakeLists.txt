cmake_minimum_required(VERSION 3.15)

project(CANFDLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CANFDLib STATIC  ${CMAKE_CURRENT_SOURCE_DIR}/src/CANFD.cpp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(Set)
include(Install)
include(Dependicies)

# For google test
add_subdirectory(test)