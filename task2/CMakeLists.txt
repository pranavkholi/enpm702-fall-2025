cmake_minimum_required(VERSION 3.22.1)
project(rwa2 VERSION 1.0 LANGUAGES C CXX)

include_directories(include)
add_executable(rwa2_pranavjagdish_koli src/main.cpp)
add_compile_options(-Wall -Wextra -pedantic-errors)

# Set C++17 standard for the targets
set_property(TARGET rwa2_pranavjagdish_koli PROPERTY CXX_STANDARD 17)
set_property(TARGET rwa2_pranavjagdish_koli PROPERTY CXX_STANDARD_REQUIRED ON)