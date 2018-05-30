cmake_minimum_required(VERSION 3.1)

project(Command)
set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    main.cpp
    BehavioralCommand.hpp
)
