cmake_minimum_required (VERSION 2.6)

find_package(WPILib)
include_directories(${WPILib_INCLUDE_DIRS})

add_library(lib-4774
  MPU6050.cpp
  I2Cdev.cpp
)

