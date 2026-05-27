cmake_minimum_required(VERSION 3.20)
project(esercitazione_10) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 CONFIG REQUIRED)
list(APPEND libraries_list PUBLIC Eigen3::Eigen)

add_executable(gradiente_Vicini gradiente_Vicini.cpp)
target_link_libraries(gradiente_Vicini ${libraries_list})

add_executable(Test_gradiente_coniugato test_gradiente_coniugato.cpp)
target_link_libraries(Test_gradiente_coniugato ${libraries_list})
add_test(NAME test_gradiente_coniugato COMMAND Test_gradiente_coniugato)

enable_testing()


