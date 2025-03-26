cmake_minimum_required (VERSION 3.1)

project(Pi-Box)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

add_executable(Pi-Box src/main.c src/window.h src/window.c src/gpio/gpio.c src/gpio/gpio.h src/Config.h src/Config.c)

find_library(wiringPi_LIB wiringPi)
target_link_libraries(Pi-Box ${wiringPi_LIB})
target_link_libraries(Pi-Box PkgConfig::GTK4)