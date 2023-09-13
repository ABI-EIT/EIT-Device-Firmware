cmake_minimum_required(VERSION 3.6)


add_library( ADG732 STATIC ADG732.cpp )
target_include_directories(ADG732 PUBLIC ./ )
target_link_libraries( ADG732 fsl_gpio )
