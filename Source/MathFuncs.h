//
// Created by 董宸 on 2021/6/19.
//

#ifndef SOURCE_MATHFUNCS_H
#define SOURCE_MATHFUNCS_H
#include <limits>
#include <cmath>
#include <cstdarg>
#include "Time.h"

namespace Math {
    namespace MathInternal{
        constexpr float FloatMinNormal = 1.17549435E-38f;
        constexpr float FloatMinDenormal = std::numeric_limits<float>::epsilon();
        constexpr bool IsFlushToZeroEnabled = (FloatMinDenormal == 0);
    }

    float Repeat(float t, float length);
    float DeltaAngle(float current, float target);

    float Sin(float f) { return sin(f); }

    float Cos(float f) { return cos(f); }

    float Tan(float f) { return tan(f); }

    float Asin(float f) { return asin(f); }

    float Acos(float f) { return acos(f); }

    float Atan(float f) { return atan(f); }

    float Atan(float y, float x) { return atan2(y, x); }

    float Sqrt(float f) { return sqrt(f); }

    float Abs(float f) { return abs(f); }

    int Abs(int i) { return abs(i); }

    float Min(float a, float b) { return a < b ? a : b; }

    int Min(int a, int b) { return a < b ? a : b; }

    float Max(float a, float b) { return a > b ? a : b; }

    int Max(int a, int b) { return a > b ? a : b; }

    // Returns /f/ raised to power /p/.
    float Pow(float f, float p) { return pow(f, p); }

    // Returns e raised to the specified power.
    float Exp(float power) { return (float)exp(power); }

    // Returns the natural (base e) logarithm of a specified number.
    float Log(float f) { return (float)log(f); }

    // Returns the base 10 logarithm of a specified number.
    float Log10(float f) { return (float)log10(f); }

    // Returns the smallest integer greater to or equal to /f/.
    float Ceil(float f) { return (float)ceil(f); }

    // Returns the largest integer smaller to or equal to /f/.
    float Floor(float f) { return (float)floor(f); }

    // Returns /f/ rounded to the nearest integer.
    float Round(float f) { return (float)round(f); }

    // Returns the smallest integer greater to or equal to /f/.
    int CeilToInt(float f) { return (int)ceil(f); }

    // Returns the largest integer smaller to or equal to /f/.
    int FloorToInt(float f) { return (int)floor(f); }

    // Returns /f/ rounded to the nearest integer.
    int RoundToInt(float f) { return (int)round(f); }

    // Returns the sign of /f/.
    float Sign(float f) { return f >= 0.0 ? 1.0f : -1.0f; }

    // The infamous ''3.14159265358979...'' value (RO).
    const float PI = (float)3.14159265358979;

    // A representation of positive infinity (RO).
    const float Infinity = std::numeric_limits<float>::infinity();

    // A representation of negative infinity (RO).
    const float NegativeInfinity = -std::numeric_limits<float>::infinity();

    // Degrees-to-radians conversion constant (RO).
    const float Deg2Rad = PI * 2.0f / 360.0f;

    // Radians-to-degrees conversion constant (RO).
    const float Rad2Deg = 1.0f / Deg2Rad;

    // A tiny floating point value (RO).
    constexpr float Epsilon = MathInternal::IsFlushToZeroEnabled ? MathInternal::FloatMinNormal
                                                  : MathInternal::FloatMinDenormal;


    // Clamps a value between a minimum float and maximum float value.
    float Clamp(float value, float min, float max);

    // Clamps value between min and max and returns value.
    // Set the position of the transform to be that of the time
    // but never less than 1 or more than 3
    //
    int Clamp(int value, int min, int max);

    // Clamps value between 0 and 1 and returns value
    float Clamp01(float value);

    // Interpolates between /a/ and /b/ by /t/. /t/ is clamped between 0 and 1.
    float Lerp(float a, float b, float t);

    // Interpolates between /a/ and /b/ by /t/ without clamping the interpolant.
    float LerpUnclamped(float a, float b, float t);

    // Same as ::ref::Lerp but makes sure the values interpolate correctly when they wrap around 360 degrees.
    float LerpAngle(float a, float b, float t);

    // Moves a value /current/ towards /target/.
    float MoveTowards(float current, float target, float maxDelta);

    // Same as ::ref::MoveTowards but makes sure the values interpolate correctly when they wrap around 360 degrees.
    float MoveTowardsAngle(float current, float target, float maxDelta);

    // Interpolates between /min/ and /max/ with smoothing at the limits.
    float SmoothStep(float from, float to, float t);

    //*undocumented
    float Gamma(float value, float absmax, float gamma);

    // Compares two floating point values if they are similar.
    bool Approximately(float a, float b);

    float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed);

    float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime);

    // Gradually changes a value towards a desired goal over time.
    float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);


    float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed);

    float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime);

    // Gradually changes an angle given in degrees towards a desired goal angle over time.
    float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

    // Loops the value t, so that it is never larger than length and never smaller than 0.
    float Repeat(float t, float length);

    // PingPongs the value t, so that it is never larger than length and never smaller than 0.
    float PingPong(float t, float length);

    // Calculates the ::ref::Lerp parameter between of two values.
    float InverseLerp(float a, float b, float value);

    // Calculates the shortest difference between two given angles.
    float DeltaAngle(float current, float target);

//    long RandomToLong(System.Random r)
//    {
//        var buffer = new byte[8];
//        r.NextBytes(buffer);
//        return (long)(System.BitConverter.ToUInt64(buffer, 0) & System.Int64.MaxValue);
//    }

    unsigned int NextPowerOfTwo(unsigned int value);

    unsigned int ClosestPowerOfTwo(unsigned int v);

    bool IsPowerOfTwo(int value);


    // http://www.opengl.org/registry/specs/EXT/framebuffer_sRGB.txt
    // http://www.opengl.org/registry/specs/EXT/texture_sRGB_decode.txt
    // {  cs / 12.92,                 cs <= 0.04045 }
    // {  ((cs + 0.055)/1.055)^2.4,   cs >  0.04045 }
    float GammaToLinearSpace(float value);


    // http://www.opengl.org/registry/specs/EXT/framebuffer_sRGB.txt
    // http://www.opengl.org/registry/specs/EXT/texture_sRGB_decode.txt
    // {  0.0,                          0         <= cl
    // {  12.92 * c,                    0         <  cl < 0.0031308
    // {  1.055 * cl^0.41666 - 0.055,   0.0031308 <= cl < 1
    // {  1.0,                                       cl >= 1  <- This has been adjusted since we want to maintain HDR colors
    float LinearToGammaSpace(float value);

};



#endif //SOURCE_MATHFUNCS_H
