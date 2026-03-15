cmake_minimum_required(VERSION 3.16)

project(Plague-Simulation LANGUAGES C)

set(CMAKE_C\_STANDARD 11)
set(CMAKE_C\_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Plague-Simulation
    src/main.c
    src/simulation.c
)

target_include_directories(Plague-Simulation
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
