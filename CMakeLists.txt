cmake_minimum_required(VERSION 3.13.0)
set (CMAKE_CXX_STANDART 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

project(Mayhem VERSION 1.0.0)

find_package (SFML 2.5 COMPONENTS system window graphics REQUIRED)
find_package(nlohmann_json REQUIRED)

# set(MY_COMPILE_FLAGS "-D _DEBUG -ggdb3 -std=c++17 -O2 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr -pie -Wlarger-than=8192 -Wstack-usage=8192")
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MY_COMPILE_FLAGS}")
add_executable(game)
add_executable(test_engine)
add_subdirectory(src)
add_subdirectory(tests)

if (RELEASE)
    add_definitions(-DDEBUG=1)
endif()

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${SFML_INCLUDE_DIR})
target_link_libraries(game sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)

enable_testing()

#GTest
find_package(GTest REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#Prepare files for testing
set(RANGE "0;1;2;3")
foreach(NUM ${RANGE})
    configure_file(tests/test_deck${NUM}.json test_deck${NUM}.json COPYONLY)
endforeach()

#Tests
target_include_directories(test_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_engine gtest gtest_main)
target_link_libraries(test_engine sfml-graphics sfml-window sfml-system nlohmann_json::nlohmann_json)
add_test(test_engine test_engine)
