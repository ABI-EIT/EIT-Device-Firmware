cmake_minimum_required(VERSION 3.6)


add_library( AD5262 STATIC AD5262.cpp )
target_include_directories(AD5262 PUBLIC ./ )
target_link_libraries( AD5262 fsl_gpio fsl_dspi )
