cmake_minimum_required(VERSION 3.17)
project(MathLib)

set(CMAKE_DEBUG_POSTFIX "d")
	set(CMAKE_RELEASE_POSTFIX "")
	set(CMAKE_MINSIZEREL_POSTFIX "msr")
	set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
  
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin")

add_library(MathLib)

target_include_directories(MathLib PUBLIC .)
target_sources(MathLib
        PUBLIC
        "Vector3.cpp"
        "Vector3.h"
        "Vector2.cpp"
        "Vector2.h"
        "Vector4.cpp"
        "Vector4.h"
        "Bound.cpp"
        "Bound.h"
        "Color.cpp"
        "Color.h"
        "MathFuncs.cpp"
        "MathFuncs.h"
        "Matrix3x3.cpp"
        "Matrix3x3.h"
        "Matrix4x4.cpp"
        "Matrix4x4.h"
        "PerlinNoise.cpp"
        "PerlinNoise.h"
        "Quaternion.cpp"
        "Quaternion.h"
        "Ray.cpp"
        "Ray.h"
        "Time.cpp"
        "Time.h"
        "Utility.cpp"
        "Utility.h" 
        "Plane.h" 
        "Plane.cpp")

        
