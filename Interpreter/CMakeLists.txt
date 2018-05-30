cmake_minimum_required(VERSION 3.1)

project(Interpreter)
set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
    MathLexer.hpp
)
