cmake_minimum_required(VERSION 3.6)

project(SEGGER ASM C )

include_directories(
    ./
)

add_library(SEGGER_HardFault_Handler STATIC HardFault_Handler.S HardFault_Handler.c)

add_library(SEGGER_SVC_Handler STATIC SVC_Handler.S)

add_library(SEGGER_SEMIHOST STATIC  SEGGER_SEMIHOST.c SEGGER_SEMIHOST_CortexM.S  )
