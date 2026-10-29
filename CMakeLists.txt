cmake_minimum_required(VERSION 3.10)
project(TercerCorteEjer3)

set(CMAKE_CXX_STANDARD 17)

add_executable(underground underground_system.cpp)
add_executable(atm atm_machine.cpp)
add_executable(auction auction_system.cpp)
