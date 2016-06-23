cmake_minimum_required(VERSION 3.3)
project(projetSEieee)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES projetIEEE_754_PierreKURZAWSKI.cpp)
add_executable(projetSEieee ${SOURCE_FILES})