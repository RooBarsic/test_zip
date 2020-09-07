cmake_minimum_required(VERSION 3.17)
project(smart_zip)

set(CMAKE_CXX_STANDARD 14)

add_executable(smart_zip main.cpp alphabet.cpp alphabet.h utills.cpp utills.h encoder.cpp encoder.h structures.h)