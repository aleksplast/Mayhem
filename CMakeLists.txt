cmake_minimum_required(VERSION 3.13.0)
set (CMAKE_CXX_STANDART 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(Mayhem VERSION 1.0.0)

find_package (SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(game)
add_subdirectory(src)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})
target_link_libraries(game sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)
