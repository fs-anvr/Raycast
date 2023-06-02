cmake_minimum_required(VERSION 3.20)
project(Engine)

add_subdirectory(Dependencies)
add_subdirectory(Tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(Engine main.cpp Engine/result/BaseResult.hpp Engine/result/Result.hpp)
