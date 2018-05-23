cmake_minimum_required(VERSION 2.8)

project(ChainOfResponsibility)
add_executable(${PROJECT_NAME}
   main.cpp
   PointerChain.hpp
   BrokerChain.hpp
   SignalAndSlots.hpp
)
