//
// Created by 董宸 on 2021/6/19.
//

#include "MathFuncs.h"

namespace Math {
    float Clamp(float value, float min, float max)
    {
        if (value < min)
            value = min;
        else if (value > max)
            value = max;
        return value;
    }

    int Clamp(int value, int min, int max)
    {
        if (value < min)
        value = min;
        else if (value > max)
        value = max;
        return value;
    }

    float Clamp01(float value)
    {
        if (value < 0.0F)
            return 0.0F;
        else if (value > 1.0F)
            return 1.0F;
        else
            return value;
    }

    float Lerp(float a, float b, float t)
    {
        return a + (b - a) * Clamp01(t);
    }

    float LerpUnclamped(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    float LerpAngle(float a, float b, float t)
    {
        float delta = Repeat((b - a), 360);
        if (delta > 180)
            delta -= 360;
        return a + delta * Clamp01(t);
    }

    float MoveTowards(float current, float target, float maxDelta)
    {
        if (abs(target - current) <= maxDelta)
            return target;
        return current + Sign(target - current) * maxDelta;
    }

    float MoveTowardsAngle(float current, float target, float maxDelta)
    {
        float deltaAngle = DeltaAngle(current, target);
        if (-maxDelta < deltaAngle && deltaAngle < maxDelta)
            return target;
        target = current + deltaAngle;
        return MoveTowards(current, target, maxDelta);
    }

    float SmoothStep(float from, float to, float t)
    {
        t = Clamp01(t);
        t = -2.0F * t * t * t + 3.0F * t * t;
        return to * t + from * (1.0F - t);
    }

    float Gamma(float value, float absmax, float gamma)
    {
        bool negative = value < 0.0F;
        float absval = Abs(value);
        if (absval > absmax)
            return negative ? -absval : absval;

        float result = Pow(absval / absmax, gamma) * absmax;
        return negative ? -result : result;
    }

    bool Approximately(float a, float b)
    {
        // If a or b is zero, compare that the other is less or equal to epsilon.
        // If neither a or b are 0, then find an epsilon that is good for
        // comparing numbers at the maximum magnitude of a and b.
        // Floating points have about 7 significant digits, so
        // 1.000001f can be represented while 1.0000001f is rounded to zero,
        // thus we could use an epsilon of 0.000001f for comparing values close to 1.
        // We multiply this epsilon by the biggest magnitude of a and b.
        return Abs(b - a) < Max(0.000001f * Max(Abs(a), Abs(b)), Epsilon * 8);
    }

    float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed)
    {
        float deltaTime = Time::deltaTime;
        return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
    }

    float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime)
    {
        float deltaTime = Time::deltaTime;
        float maxSpeed = Infinity;
        return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
    }

    // Gradually changes a value towards a desired goal over time.
    float SmoothDamp(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
    {
        // Based on Game Programming Gems 4 Chapter 1.10
        smoothTime = Max(0.0001F, smoothTime);
        float omega = 2.0F / smoothTime;

        float x = omega * deltaTime;
        float exp = 1.0F / (1.0F + x + 0.48F * x * x + 0.235F * x * x * x);
        float change = current - target;
        float originalTo = target;

        // Clamp maximum speed
        float maxChange = maxSpeed * smoothTime;
        change = Clamp(change, -maxChange, maxChange);
        target = current - change;

        float temp = (currentVelocity + omega * change) * deltaTime;
        currentVelocity = (currentVelocity - omega * temp) * exp;
        float output = target + (change + temp) * exp;

        // Prevent overshooting
        if (originalTo - current > 0.0F == output > originalTo)
        {
            output = originalTo;
            currentVelocity = (output - originalTo) / deltaTime;
        }

        return output;
    }

    float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed)
    {
        float deltaTime = Time::deltaTime;
        return SmoothDampAngle(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
    }

    float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime)
    {
        float deltaTime = Time::deltaTime;
        float maxSpeed = Infinity;
        return SmoothDampAngle(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
    }

    float SmoothDampAngle(float current, float target, float& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
    {
        target = current + DeltaAngle(current, target);
        return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
    }

    float Repeat(float t, float length)
    {
        return Clamp(t - floor(t / length) * length, 0.0f, length);
    }

    float PingPong(float t, float length)
    {
        t = Repeat(t, length * 2.0F);
        return length - abs(t - length);
    }

    float InverseLerp(float a, float b, float value)
    {
        if (a != b)
            return Clamp01((value - a) / (b - a));
        else
            return 0.0f;
    }

    float DeltaAngle(float current, float target)
    {
        float delta = Repeat((target - current), 360.0F);
        if (delta > 180.0F)
            delta -= 360.0F;
        return delta;
    }

    unsigned int NextPowerOfTwo(unsigned int value)
    {
        unsigned int v = value;
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    unsigned int ClosestPowerOfTwo(unsigned int v)
    {
        unsigned int nextPower = NextPowerOfTwo (v);
        unsigned int prevPower = nextPower >> 1;
        if (v - prevPower < nextPower - v)
            return prevPower;
        else
            return nextPower;
    }

    bool IsPowerOfTwo(int value)
    {
        if (value == 0)
            return false;

        return (int)(Ceil((Log(value) /
                           Log(2)))) ==
               (int)(Floor(((Log(value) /
                             Log(2)))));
    }

    // http://www.opengl.org/registry/specs/EXT/framebuffer_sRGB.txt
    // http://www.opengl.org/registry/specs/EXT/texture_sRGB_decode.txt
    // {  cs / 12.92,                 cs <= 0.04045 }
    // {  ((cs + 0.055)/1.055)^2.4,   cs >  0.04045 }
    float GammaToLinearSpace(float value)
    {
        if (value <= 0.04045F)
            return value / 12.92F;
        else if (value < 1.0F)
            return Pow((value + 0.055F)/1.055F, 2.4F);
        else
            return Pow(value, 2.4F);
    }

    float LinearToGammaSpace(float value)
    {
        if (value <= 0.0F)
            return 0.0F;
        else if (value <= 0.0031308F)
            return 12.92F * value;
        else if (value <= 1.0F)
            return 1.055F * Pow(value, 0.41666F) - 0.055F;
        else
            return Pow(value, 0.41666F);
    }
}