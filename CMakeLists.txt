cmake_minimum_required(VERSION 3.27)
project(Ray_Tracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(Ray_Tracer main.cpp
        lib/vec3.h
        lib/color.h
        lib/ray.h
        lib/hittable.h
        lib/sphere.h
        lib/hittable_list.h
        lib/commons.h
        lib/interval.h
        lib/camera.h
        lib/material.h)
MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

