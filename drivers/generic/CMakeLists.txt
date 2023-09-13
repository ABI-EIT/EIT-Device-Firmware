cmake_minimum_required(VERSION 3.6)

project(generic)

include_directories(
    ./
    ./cmsis_drivers
    ./drivers
    ./utilities
)

add_library( Generic_stdlib_stubs STATIC ./stdlib_stubs.c )
target_link_libraries( Generic_stdlib_stubs CMSIS )