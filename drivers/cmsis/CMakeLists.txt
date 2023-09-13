
project(CMSIS)

include_directories(
    ./
    ./Core/Include
    ./DAP/Include
    ./Driver/Include
    #./DSP/Include
    #./NN/Include
    #./RTOS/RTX/INC
)

add_library( CMSIS STATIC Core/core.c )
target_include_directories( CMSIS PUBLIC ./Core/Include ./Driver/Include)
