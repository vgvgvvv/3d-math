//
// Created by 董宸 on 2021/6/19.
//

#ifndef SOURCE_UTILITY_H
#define SOURCE_UTILITY_H

#include "MathFuncs.h"
#include <limits>
#include <iostream>

#define FLOAT_INFINITY (std::numeric_limits<float>::infinity())

#define INT_INFINITY (std::numeric_limits<int>::infinity())

#define DOUBLE_INFINITY (std::numeric_limits<double>::infinity())

#ifndef NDEBUG
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

class Utility {

};


#endif //SOURCE_UTILITY_H
