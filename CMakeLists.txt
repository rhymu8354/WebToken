# CMakeLists.txt for WebToken
#
# © 2019 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This WebToken)

set(Headers
    include/WebToken/WebToken.hpp
)

set(Sources
    src/WebToken.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES
    FOLDER Libraries
)

target_include_directories(${This} PUBLIC include)

target_link_libraries(${This} PUBLIC
    Base64
    Json
    SystemAbstractions
)

add_subdirectory(test)
