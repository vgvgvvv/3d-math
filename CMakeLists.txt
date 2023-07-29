cmake_minimum_required(VERSION 3.17)
project(MathLib)

if(NOT REMAKE_SOURCE_DIR)
	include(FetchContent)
	FetchContent_Declare(
	  re-cmake
	  GIT_REPOSITORY https://github.com/vgvgvvv/re-cmake
	  GIT_TAG        "test-1.0"
	)
	FetchContent_MakeAvailable(re-cmake)

	list(APPEND CMAKE_MODULE_PATH "${re-cmake_SOURCE_DIR}")
	set(REMAKE_SOURCE_DIR ${re-cmake_SOURCE_DIR})

	message(STATUS "MathLib pulled REMAKE_SOURCE_DIR = ${REMAKE_SOURCE_DIR}")

else()

	message(STATUS "MathLib existed REMAKE_SOURCE_DIR = ${REMAKE_SOURCE_DIR}")

endif()

include(${REMAKE_SOURCE_DIR}/Init.cmake)

ReMake_InitProject()
set(TargetName MathLib)

if(${CMAKE_CURRENT_SOURCE_DIR}} STREQUAL ${REMAKE_ROOT_PATH})

	ReMake_Log(${TargetName} "auto add target MathLib")

	ReMake_AddTarget(
	  TARGET_NAME ${TargetName}
	  MODE SHARED
	)

else ()

	ReMake_Log(${TargetName} "not root project please add by project CMakeList.txt")

endif()