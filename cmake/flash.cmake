# cmake config for generating build information and a hex file for flashing
#
# Copyright (c) 
#   2021 Joshua BRADFIELD (joshbradfield@gmail.com, jbra107@aucklanduni.ac.nz)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "echo" "Generating output files..."
    COMMAND "${CMAKE_OBJDUMP}" -S $<TARGET_FILE_NAME:${PROJECT_NAME}> > ${PROJECT_NAME}.$<LOWER_CASE:$<CONFIG>>.lst
    COMMAND "${CMAKE_NM}" -C -l -n -S $<TARGET_FILE_NAME:${PROJECT_NAME}> > ${PROJECT_NAME}.$<LOWER_CASE:$<CONFIG>>.sym
    COMMAND "${CMAKE_OBJCOPY}" -Oihex $<TARGET_FILE_NAME:${PROJECT_NAME}> -R .eeprom ${PROJECT_NAME}.$<LOWER_CASE:$<CONFIG>>.hex
    COMMAND "${CMAKE_SIZE}" $<TARGET_FILE_NAME:${PROJECT_NAME}> > ${PROJECT_NAME}.$<LOWER_CASE:$<CONFIG>>.size
    COMMAND "${CMAKE_SIZE}" $<TARGET_FILE_NAME:${PROJECT_NAME}>
)
