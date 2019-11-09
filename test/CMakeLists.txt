# CMakeLists.txt for WebTokenTests
#
# © 2019 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This WebTokenTests)

set(Sources
    src/WebTokenTests.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_include_directories(${This} PRIVATE ..)

target_link_libraries(${This} PUBLIC
    gtest_main
    Json
    WebToken
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
