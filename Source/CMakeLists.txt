cmake_minimum_required(VERSION 3.17)
project(Source)

set(CMAKE_CXX_STANDARD 14)

add_library(MathLib)

target_include_directories(MathLib PUBLIC .)
target_sources(MathLib
        PUBLIC
        Vector3.cpp
        Vector3.h
        Vector2.cpp
        Vector2.h
        Vector4.cpp
        Vector4.h
        Bound.cpp
        Bound.h
        Color.cpp
        Color.h
        MathFuncs.cpp
        MathFuncs.h
        Matrix3x3.cpp
        Matrix3x3.h
        Matrix4x4.cpp
        Matrix4x4.h
        PerlinNoise.cpp
        PerlinNoise.h
        Quaternion.cpp
        Quaternion.h
        Ray.cpp
        Ray.h
        Time.cpp
        Time.h
        Utility.cpp
        Utility.h)