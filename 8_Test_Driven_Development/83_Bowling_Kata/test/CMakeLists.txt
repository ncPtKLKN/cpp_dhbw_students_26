cmake_minimum_required(VERSION 3.16)

set(This gameTest)

set(Sources
    gameTest.cpp)

add_executable(${This} ${Sources})
target_include_directories(${This} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${This} PUBLIC
    GTest::gtest_main
    bowling_kata
)

include(GoogleTest)
gtest_discover_tests(${This} DISCOVERY_TIMEOUT 60)