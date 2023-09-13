cmake_minimum_required(VERSION 3.6)
###############################################################################
# CMake script for building with the teensy 3.6 ( MK66FX1M0xxx18 )            #
#                                                                             #
# Copyright (c)                                                               #
#   2021 Joshua BRADFIELD (joshbradfield@gmail.com, jbra107@aucklanduni.ac.nz)#
###############################################################################

# NB : IF YOU EDIT THIS FILE YOU NEED TO REGENERATE THE MAKE FILES

###############################################################################
# Options                                                                     #
###############################################################################

# Place all application sources here, then regenerate the make files
set(sources 
    src/main.cpp
)

# Place all used drivers here, then regenerate the make files
set(drivers 
    fsl_gpio
    fsl_assert_simple
    fsl_clock
    fsl_smc
    fsl_adc16
    fsl_dmamux
    fsl_edma
    fsl_pdb
    fsl_dac
    ADG732
    AD5262
    AD9833
)

# Set to TRUE to enable semihosting ( debug only )
#   This allows printf to work when the debugger is attached.
set(ENABLE_SEMIHOSTING FALSE) 

# Set to TRUE to use the arduino base, 
#   - When false a generic baremetal base will be used
set(USE_ARDUINO TRUE) 
set(F_CPU 180000000)
set(F_BUS  90000000)

###############################################################################

# project name
project(firmware)

# Linker script
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/ld/MK66FX1M0xxx18.ld")


# define CPU OPTIONS
set(CPU_OPTIONS 
    -mthumb -march=armv7e-m -mtune=cortex-m4 -MMD
    -DCPU_MK66FX1M0VMD18
    -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant 
)

add_compile_options(
    ${CPU_OPTIONS}
    $<$<COMPILE_LANGUAGE:C>:-std=gnu11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++17>

    $<$<COMPILE_LANGUAGE:CXX>:-fms-extensions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    $<$<COMPILE_LANGUAGE:CXX>:-felide-constructors>
    -fstrict-volatile-bitfields
    -ffunction-sections
    -fdata-sections

    #$<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>
    #$<$<COMPILE_LANGUAGE:CXX>:-Wsuggest-override>
    #$<$<COMPILE_LANGUAGE:CXX>:-Werror>           
    #-Wall                  
    #-Wextra                
    #-Wcast-align           
    #-Wconversion           
    #-Wsign-conversion      
    #-Wshadow               
    #-Wlogical-op           
    #-Wsuggest-final-types  
    #-Wsuggest-final-methods

    #-pedantic

    $<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_SEMIHOSTING}>>:-DSEMIHOSTING>
    $<$<CONFIG:Debug>:-DDEBUG>

    $<$<BOOL:${USE_ARDUINO}>:-DARDUINO=10805>
    $<$<BOOL:${USE_ARDUINO}>:-DTEENSYDUINO=144>
    $<$<BOOL:${USE_ARDUINO}>:-DF_CPU=${F_CPU}>
    $<$<BOOL:${USE_ARDUINO}>:-DF_BUS=${F_BUS}>
    $<$<BOOL:${USE_ARDUINO}>:-DUSB_SERIAL>
    

    #-D__USE_CMSIS
    #-DDISABLE_WDOG
    
)

add_link_options(
    ${CPU_OPTIONS}
    -Os
    -Wl,--gc-sections,--relax,--defsym=__rtc_localtime=0   #,--defsym=__rtc_localtime={extra.time.local}
    -T ${LINKER_SCRIPT}
    -mthumb
    -mcpu=cortex-m4
    -lm
    --specs=nano.specs
    #$<$<AND:$<CONFIG:Debug>,$<NOT:$<BOOL:${ENABLE_SEMIHOSTING}>>>:-nostartfiles>
    $<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_SEMIHOSTING}>>:--specs=rdimon.specs>
    $<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_SEMIHOSTING}>>:-lc>
    $<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_SEMIHOSTING}>>:-lrdimon>
    $<$<AND:$<CONFIG:Debug>,$<BOOL:${ENABLE_SEMIHOSTING}>>:-u_printf_float>
    #$<$<AND:$<CONFIG:Debug>,$<NOT:$<BOOL:${ENABLE_SEMIHOSTING}>>>:-nostdlib>
)


add_subdirectory(./drivers/devices/MK66F18)
add_subdirectory(./drivers/segger)
add_subdirectory(./drivers/generic)
add_subdirectory(./drivers/cmsis)
add_subdirectory(./drivers/boards/)
add_subdirectory(./drivers/external/)

include_directories(
    ./src
)


# list of modules to build final firmware (without extension .c or .cpp)
add_executable(${PROJECT_NAME} ${sources} )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    $<$<BOOL:${USE_ARDUINO}>:Arduino>
    $<$<NOT:$<BOOL:${USE_ARDUINO}>>:MK66F18_startup>
    CMSIS
    $<$<NOT:$<BOOL:${USE_ARDUINO}>>:SEGGER_HardFault_Handler>
    $<$<NOT:$<BOOL:${USE_ARDUINO}>>:MK66F18_default_handlers>
    $<$<NOT:$<BOOL:${USE_ARDUINO}>>:Generic_stdlib_stubs>
    ${drivers}
)


SET (CMAKE_EXECUTABLE_SUFFIX ".elf")

set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME_DEBUG   "${PROJECT_NAME}.debug")
set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME_RELEASE "${PROJECT_NAME}.release")

include("cmake/flash.cmake")