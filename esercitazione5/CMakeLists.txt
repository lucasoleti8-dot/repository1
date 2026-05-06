cmake_minimum_required(VERSION 3.20)
project(esercitazione_4) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

set(SOURCE_measure_sorts measure_sorts.cpp timecounter.cpp)
add_executable(Measure_sorts ${SOURCE_measure_sorts})

set(SOURCE_mergesort test_mergesort.cpp)
add_executable(Test_mergesort ${SOURCE_mergesort})
add_test(NAME mergesort COMMAND Test_mergesort)

set(SOURCE_quicksort test_quicksort.cpp)
add_executable(Test_quicksort ${SOURCE_quicksort})
add_test(NAME quicksort COMMAND Test_quicksort)

enable_testing()