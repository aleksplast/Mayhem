cmake_minimum_required(VERSION 3.0)
project(Mayhem VERSION 1.0.0)

set(CORE_DIR ${CMAKE_SOURCE_DIR}/src/core)
set(GRAPHICS_DIR ${CMAKE_SOURCE_DIR}/src/graphics)
set(PARSER_DIR ${CMAKE_SOURCE_DIR}/src/parser)
set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/src/engine)

set(sources ${CORE_DIR}/card.cpp ${ENGINE_DIR}/engine.cpp ${ENGINE_DIR}/playground.cpp ${ENGINE_DIR}/player.cpp ${GRAPHICS_DIR}/graphics.cpp ${GRAPHICS_DIR}/draw.cpp ${GRAPHICS_DIR}/drawable.cpp ${GRAPHICS_DIR}/button.cpp ${PARSER_DIR}/parser.cpp ${CMAKE_SOURCE_DIR}/src/main.cpp)
find_package (SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(game)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})
target_link_libraries(game sfml-graphics sfml-window sfml-system)
target_sources(game PRIVATE ${sources})
