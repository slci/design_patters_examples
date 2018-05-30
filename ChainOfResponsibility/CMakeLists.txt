cmake_minimum_required(VERSION 3.1)

project(ChainOfResponsibility)
set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
   main.cpp
   PointerChain.hpp
   BrokerChain.hpp
   SignalAndSlots.hpp
)
