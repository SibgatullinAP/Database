cmake_minimum_required(VERSION 2.8)

project(DataBase)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -mfpmath=sse -Ofast -flto -march=native -funroll-loops -DZACHET -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format ")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")

file(GLOB CPPS "*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})
