//
// Created by 董宸 on 2021/6/19.
//

#pragma once

#include "MathFuncs.h"
#include <limits>
#include <iostream>

#define FLOAT_INFINITY (std::numeric_limits<float>::infinity())

#define INT_INFINITY (std::numeric_limits<int>::infinity())

#define DOUBLE_INFINITY (std::numeric_limits<double>::infinity())

#ifndef DEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif


template <class T>
void Swap(T & a, T & b)
{
    std::swap(a, b);
}

