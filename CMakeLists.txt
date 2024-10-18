cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(BitArray VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(lib)

target_include_directories(BitArrayLib PUBLIC .) # PRIVATE

add_executable(BitArrayMain main.cpp)

target_link_libraries(BitArrayMain BitArrayLib)

add_subdirectory(tests)
