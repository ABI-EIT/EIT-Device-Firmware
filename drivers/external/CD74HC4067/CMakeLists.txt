cmake_minimum_required(VERSION 3.6)


add_library( CD74HC4067 STATIC CD74HC4067.cpp )
target_include_directories(CD74HC4067 PUBLIC ./ )
target_link_libraries( CD74HC4067 fsl_gpio )
