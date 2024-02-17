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
        lib/camera.h)


