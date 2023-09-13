cmake_minimum_required(VERSION 3.6)

project(MK66F18)

include_directories(
    ./
    ./cmsis_drivers
    ./drivers
    ./utilities
)


add_library( MK66F18_startup STATIC ./startup/startup_baremetal.c )

add_library( MK66F18_default_handlers STATIC ./default_handlers.c )

add_library( ${PROJECT_NAME} STATIC system_MK66F18.c)
target_include_directories( ${PROJECT_NAME} PUBLIC ./ ./drivers )
target_link_libraries( ${PROJECT_NAME} CMSIS )


function(Add_Custom_Library driver_name driver_path ) # ARGVN = additional_deps
    add_library( ${driver_name} STATIC ${driver_path}/${driver_name}.c )
    target_include_directories( ${driver_name} PUBLIC ${driver_path} )
    target_link_libraries( ${driver_name} fsl_common ${ARGN} )
endfunction()

function(Add_Driver_Library driver_name ) # ARGN = additional_deps
Add_Custom_Library( ${driver_name} drivers ${ARGN} )
endfunction()

# Drivers

add_library( fsl_common STATIC drivers/fsl_common.c )
target_include_directories( fsl_common PUBLIC ./ ./drivers )
target_link_libraries( fsl_common ${PROJECT_NAME} )


Add_Driver_Library( fsl_adc16 )
Add_Driver_Library( fsl_cache )
Add_Driver_Library( fsl_clock )
Add_Driver_Library( fsl_cmp )
Add_Driver_Library( fsl_cmt )
Add_Driver_Library( fsl_crc )
Add_Driver_Library( fsl_dac )
Add_Driver_Library( fsl_dmamux )
Add_Driver_Library( fsl_dspi_edma )
Add_Driver_Library( fsl_dspi )
Add_Driver_Library( fsl_edma )
Add_Driver_Library( fsl_enet )
Add_Driver_Library( fsl_ewm )
Add_Driver_Library( fsl_flexbus )
Add_Driver_Library( fsl_flexcan )
Add_Driver_Library( fsl_ftfx_cache )
Add_Driver_Library( fsl_ftfx_controller )
Add_Driver_Library( fsl_ftfx_flash )
Add_Driver_Library( fsl_ftfx_flexnvm )
Add_Driver_Library( fsl_ftm )
Add_Driver_Library( fsl_gpio )
Add_Driver_Library( fsl_i2c_edma )
Add_Driver_Library( fsl_i2c )
Add_Driver_Library( fsl_llwu )
Add_Driver_Library( fsl_lmem_cache )
Add_Driver_Library( fsl_lptmr )
Add_Driver_Library( fsl_lpuart_edma )
Add_Driver_Library( fsl_lpuart )
Add_Driver_Library( fsl_pdb )
Add_Driver_Library( fsl_pit )
Add_Driver_Library( fsl_pmc )
Add_Driver_Library( fsl_rcm )
Add_Driver_Library( fsl_rnga )
Add_Driver_Library( fsl_rtc )
Add_Driver_Library( fsl_sai_edma )
Add_Driver_Library( fsl_sai )
Add_Driver_Library( fsl_sdhc )
Add_Driver_Library( fsl_sdramc )
Add_Driver_Library( fsl_sim )
Add_Driver_Library( fsl_smc )
Add_Driver_Library( fsl_sysmpu )
Add_Driver_Library( fsl_tpm )
Add_Driver_Library( fsl_tsi_v4 )
Add_Driver_Library( fsl_uart_edma )
Add_Driver_Library( fsl_uart )
Add_Driver_Library( fsl_vref )
Add_Driver_Library( fsl_wdog )

# Utilities

Add_Custom_Library( fsl_str                       ./utilities/str )

Add_Custom_Library( fsl_debug_console             ./utilities/debug_console      fsl_str )
Add_Custom_Library( fsl_debug_console_lite        ./utilities/debug_console_lite fsl_str )

Add_Custom_Library( fsl_assert                    ./utilities                     fsl_str )
Add_Custom_Library( fsl_assert_simple             ./utilities )
Add_Custom_Library( fsl_notifier                  ./utilities )
Add_Custom_Library( fsl_shell                     ./utilities                     fsl_str  )


# Arduino



add_library( Arduino STATIC ./arduino/mk20dx128.c 
    ./arduino/analog.c
    ./arduino/AudioStream.cpp
    ./arduino/avr_emulation.cpp
    ./arduino/DMAChannel.cpp
    ./arduino/eeprom.c
    ./arduino/EventResponder.cpp
    ./arduino/HardwareSerial.cpp
    ./arduino/HardwareSerial1.cpp
    ./arduino/HardwareSerial2.cpp
    ./arduino/HardwareSerial3.cpp
    ./arduino/HardwareSerial4.cpp
    ./arduino/HardwareSerial5.cpp
    ./arduino/HardwareSerial6.cpp
    ./arduino/IntervalTimer.cpp
    ./arduino/IPAddress.cpp
    ./arduino/keylayouts.c
    ./arduino/math_helper.c   
    ./arduino/#memcpy-armv7m.S
    ./arduino/#memset.S
    ./arduino/mk20dx128.c
    ./arduino/new.cpp
    ./arduino/nonstd.c
    ./arduino/pins_teensy.c
    ./arduino/Print.cpp
    ./arduino/ser_print.c
    ./arduino/serial1.c
    ./arduino/serial2.c
    ./arduino/serial3.c
    ./arduino/serial4.c
    ./arduino/serial5.c
    ./arduino/serial6_lpuart.c
    ./arduino/serial6.c
    ./arduino/serialEvent.cpp
    ./arduino/serialEvent1.cpp
    ./arduino/serialEvent2.cpp
    ./arduino/serialEvent3.cpp
    ./arduino/serialEvent4.cpp
    ./arduino/serialEvent5.cpp
    ./arduino/serialEvent6.cpp
    ./arduino/serialEventUSB1.cpp
    ./arduino/serialEventUSB2.cpp
    ./arduino/Stream.cpp
    ./arduino/Tone.cpp
    ./arduino/touch.c
    ./arduino/usb_audio.cpp
    ./arduino/usb_desc.c
    ./arduino/usb_dev.c
    ./arduino/usb_flightsim.cpp
    ./arduino/usb_inst.cpp
    ./arduino/usb_joystick.c
    ./arduino/usb_keyboard.c
    ./arduino/usb_mem.c
    ./arduino/usb_midi.c
    ./arduino/usb_mouse.c
    ./arduino/usb_mtp.c
    ./arduino/usb_rawhid.c
    ./arduino/usb_seremu.c
    ./arduino/usb_serial.c
    ./arduino/usb_serial2.c
    ./arduino/usb_serial3.c
    ./arduino/usb_touch.c
    ./arduino/WMath.cpp
    ./arduino/WString.cpp
    ./arduino/yield.cpp       
    )
target_include_directories( Arduino PUBLIC ./arduino )
target_compile_definitions( Arduino PUBLIC _GNU_SOURCE __MK66FX1M0__=1 F_CPU=180000000 ARDUINO=10805 TEENSYDUINO=144 USB_SERIAL LAYOUT_US_ENGLISH USING_MAKEFILE )