cmake_minimum_required (VERSION 2.6)

find_package(WPILib)
include_directories(${WPILib_INCLUDE_DIRS} .)

add_definitions ("-Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-value ")

add_library(lib-4774
  subsystems/UdpReceiver.cpp
  subsystems/DropBoneImu.cpp
  commands/ReceiveUdp.cpp
)

