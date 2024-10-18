cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(BitArrayLib)
add_library(BitArrayLib STATIC bit_array_overloads_logic.cpp bit_array.hpp bit_array.cpp)