cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
 URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(bit_arr_test bit_arr_test.cpp)

target_link_libraries(bit_arr_test PRIVATE GTest::gtest_main BitArrayLib)

include(GoogleTest)
gtest_discover_tests(bit_arr_test)
