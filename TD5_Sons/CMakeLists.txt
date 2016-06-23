cmake_minimum_required(VERSION 3.2)
project(TD5_Sons)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES application.cpp MusicRecord.hpp)
add_executable(TD5_Sons ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML_Modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TD5_Sons ${SFML_LIBRARIES})
endif()