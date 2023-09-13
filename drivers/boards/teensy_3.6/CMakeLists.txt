cmake_minimum_required(VERSION 3.6)

project(TEENSY36)

include_directories(
    ./
)

add_library( ${PROJECT_NAME} STATIC board.c clock_config.c pin_mux.c peripherals.c )
target_include_directories(${PROJECT_NAME} PUBLIC ./ )

target_link_libraries( ${PROJECT_NAME}
    startup
    MK66F18
    fsl_gpio
)
