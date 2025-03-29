cmake_minimum_required (VERSION 3.1)

project(Pi-Box)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

file(GLOB pi_box_SRC
     "src/*.h"
     "src/*.c"
     "src/**/*.c"
     "src/**/*.h"
)

add_executable(Pi-Box ${pi_box_SRC})

find_library(wiringPi_LIB wiringPi)
target_link_libraries(Pi-Box ${wiringPi_LIB})
target_link_libraries(Pi-Box PkgConfig::GTK4)