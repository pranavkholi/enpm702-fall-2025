cmake_minimum_required(VERSION 3.22.1)
project(task1 VERSION 0.1.0 LANGUAGES C CXX)



include_directories(include)
add_executable(task1_cpp src/task1.cpp)

# Set C++17 standard for the target
set_property(TARGET task1_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET task1_cpp PROPERTY CXX_STANDARD_REQUIRED ON)
