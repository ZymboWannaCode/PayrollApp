cmake_minimum_required(VERSION 3.27)
project(HollyFPayroll30012024 C)

set(CMAKE_C_STANDARD 99)

add_executable(HollyFPayroll30012024 main.c RESOURCES/icon.ico)

add_executable(HollyFPayrollFinal WIN32 main.c RESOURCES/icon.ico)
