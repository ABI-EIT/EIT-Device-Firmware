cmake_minimum_required(VERSION 3.6)


add_library( AD9833 STATIC AD9833.cpp )
target_include_directories(AD9833 PUBLIC ./ )
target_link_libraries( AD9833 fsl_gpio fsl_dspi )
