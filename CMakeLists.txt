cmake_minimum_required(VERSION 3.13.0)
set (CMAKE_CXX_STANDART 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

project(Mayhem VERSION 1.0.0)

find_package (SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(game)

if (ENABLE_TESTING)
    add_executable(test_engine)
endif()

add_subdirectory(src)

if (DEBUG)
    add_definitions(-DDEBUG=1)
endif()

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})
target_link_libraries(game sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)

if (ENABLE_TESTING)
    add_subdirectory(tests)

    #GTest
    find_package(GTest REQUIRED)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    #Prepare files for testing
    set(RANGE "0;1;2;3")
    foreach(NUM ${RANGE})
        configure_file(tests/test_deck${NUM}.json test_deck${NUM}.json COPYONLY)
    endforeach()

    configure_file(tests/test_bases.json test_bases.json COPYONLY)

    #Tests
    target_include_directories(test_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(test_engine gtest gtest_main)
    target_link_libraries(test_engine sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)
    add_test(test_engine test_engine)
endif()
