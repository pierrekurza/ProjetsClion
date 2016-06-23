cmake_minimum_required(VERSION 3.2)
project(TD3_Graphique_Couleurs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp vecteurGris.hpp matriceRougeBleu.hpp cerclesTransparents.hpp)
add_executable(TD3_Graphique_Couleurs ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML_Modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TD3_Graphique_Couleurs ${SFML_LIBRARIES})
endif()