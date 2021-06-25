//
// Created by 董宸 on 2021/6/19.
//

#include "Vector2.h"
#include "Utility.h"
#include "MathTime.h"

const Vector2 Vector2::zeroVector(0.F, 0.F);
const Vector2 Vector2::oneVector(1.F, 1.F);
const Vector2 Vector2::upVector(0.F, 1.F);
const Vector2 Vector2::downVector(0.F, -1.F);
const Vector2 Vector2::leftVector(-1.F, 0.F);
const Vector2 Vector2::rightVector(1.F, 0.F);
const Vector2 Vector2::positiveInfinityVector(FLOAT_INFINITY, FLOAT_INFINITY);
const Vector2 Vector2::negativeInfinityVector(-FLOAT_INFINITY, -FLOAT_INFINITY);

float& Vector2::operator[](int index) {
    ASSERT(index == 0 || index == 1, "Vector2 Index Error!!");

    switch (index) {
        case 0: return x;
        case 1: return y;
        default:
            break;
    }
    return x;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
{
    t = Math::Clamp01(t);
    return Vector2(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t
    );
}

Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t)
{
    return Vector2(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t
    );
}

Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta)
{
    // avoid vector ops because current scripting backends are terrible at inlining
    float toVector_x = target.x - current.x;
    float toVector_y = target.y - current.y;

    float sqDist = toVector_x * toVector_x + toVector_y * toVector_y;

    if (sqDist == 0 || (maxDistanceDelta >= 0 && sqDist <= maxDistanceDelta * maxDistanceDelta))
        return target;

    float dist = (float)Math::Sqrt(sqDist);

    return Vector2(current.x + toVector_x / dist * maxDistanceDelta,
                       current.y + toVector_y / dist * maxDistanceDelta);
}

void Vector2::Normalize()
{
    float mag = magnitude();
    if (mag > Math::kEpsilon)
    {
        x = x / mag;
        y = y / mag;
    }
    else{
        x = 0;
        y = 0;
    }
}

Vector2 Vector2::normalized()
{
    Vector2 v(x, y);
    v.Normalize();
    return v;
}

Vector2 Vector2::Reflect(Vector2 inDirection, Vector2 inNormal)
{
    float factor = -2.F * Dot(inNormal, inDirection);
    return Vector2(factor * inNormal.x + inDirection.x, factor * inNormal.y + inDirection.y);
}

Vector2 Vector2::Perpendicular(Vector2 inDirection)
{
    return Vector2(-inDirection.y, inDirection.x);
}

float Vector2::Dot(Vector2 lhs, Vector2 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Vector2::magnitude()
{
	return (float)Math::Sqrt(x * x + y * y);
}

float Vector2::sqrMagnitude()
{
	return x * x + y * y;
}

float Vector2::Angle(Vector2 from, Vector2 to)
{
    // sqrt(a) * sqrt(b) = sqrt(a * b) -- valid for real numbers
    float denominator = (float)Math::Sqrt(from.sqrMagnitude() * to.sqrMagnitude());
    if (denominator < Math::kEpsilonNormalSqrt)
        return 0.F;

    float dot = Math::Clamp(Dot(from, to) / denominator, -1.F, 1.F);
    return (float)Math::Acos(dot) * Math::Rad2Deg;
}

float Vector2::SignedAngle(Vector2 from, Vector2 to)
{
    float unsigned_angle = Angle(from, to);
    float sign = Math::Sign(from.x * to.y - from.y * to.x);
    return unsigned_angle * sign;
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
    float diff_x = a.x - b.x;
    float diff_y = a.y - b.y;
    return (float)Math::Sqrt(diff_x * diff_x + diff_y * diff_y);
}

Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength)
{
    float sqrMagnitude = vector.sqrMagnitude();
    if (sqrMagnitude > maxLength * maxLength)
    {
        float mag = (float)Math::Sqrt(sqrMagnitude);

        //these intermediate variables force the intermediate result to be
        //of float precision. without this, the intermediate result can be of higher
        //precision, which changes behavior.
        float normalized_x = vector.x / mag;
        float normalized_y = vector.y / mag;
        return Vector2(normalized_x * maxLength,
                           normalized_y * maxLength);
    }
    return vector;
}

float Vector2::SqrMagnitude(Vector2 a)
{
	return a.x * a.x + a.y * a.y;
}

float Vector2::SqrMagnitude()
{
	return x * x + y * y;
}

Vector2 Vector2::Min(Vector2 lhs, Vector2 rhs)
{
	return Vector2(Math::Min(lhs.x, rhs.x), Math::Min(lhs.y, rhs.y));
}

Vector2 Vector2::Max(Vector2 lhs, Vector2 rhs)
{
	return Vector2(Math::Max(lhs.x, rhs.x), Math::Max(lhs.y, rhs.y));
}

Vector2 Vector2::SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime, float maxSpeed)
{
    float deltaTime = Time::deltaTime;
    return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

Vector2 Vector2::SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime)
{
    float deltaTime = Time::deltaTime;
    float maxSpeed = Math::Infinity;
    return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

Vector2 Vector2::SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
    // Based on Game Programming Gems 4 Chapter 1.10
    smoothTime = Math::Max(0.0001F, smoothTime);
    float omega = 2.F / smoothTime;

    float x = omega * deltaTime;
    float exp = 1.F / (1.F + x + 0.48F * x * x + 0.235F * x * x * x);

    float change_x = current.x - target.x;
    float change_y = current.y - target.y;
    Vector2 originalTo = target;

    // Clamp maximum speed
    float maxChange = maxSpeed * smoothTime;

    float maxChangeSq = maxChange * maxChange;
    float sqDist = change_x * change_x + change_y * change_y;
    if (sqDist > maxChangeSq)
    {
        auto mag = (float)Math::Sqrt(sqDist);
        change_x = change_x / mag * maxChange;
        change_y = change_y / mag * maxChange;
    }

    target.x = current.x - change_x;
    target.y = current.y - change_y;

    float temp_x = (currentVelocity.x + omega * change_x) * deltaTime;
    float temp_y = (currentVelocity.y + omega * change_y) * deltaTime;

    currentVelocity.x = (currentVelocity.x - omega * temp_x) * exp;
    currentVelocity.y = (currentVelocity.y - omega * temp_y) * exp;

    float output_x = target.x + (change_x + temp_x) * exp;
    float output_y = target.y + (change_y + temp_y) * exp;

    // Prevent overshooting
    float origMinusCurrent_x = originalTo.x - current.x;
    float origMinusCurrent_y = originalTo.y - current.y;
    float outMinusOrig_x = output_x - originalTo.x;
    float outMinusOrig_y = output_y - originalTo.y;

    if (origMinusCurrent_x * outMinusOrig_x + origMinusCurrent_y * outMinusOrig_y > 0)
    {
        output_x = originalTo.x;
        output_y = originalTo.y;

        currentVelocity.x = (output_x - originalTo.x) / deltaTime;
        currentVelocity.y = (output_y - originalTo.y) / deltaTime;
    }
    return Vector2(output_x, output_y);
}

bool Vector2::LineIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& result)
{
    float bx = p2.x - p1.x;
    float by = p2.y - p1.y;
    float dx = p4.x - p3.x;
    float dy = p4.y - p3.y;
    float bDotDPerp = bx * dy - by * dx;
    if (bDotDPerp == 0)
    {
        return false;
    }
    float cx = p3.x - p1.x;
    float cy = p3.y - p1.y;
    float t = (cx * dy - cy * dx) / bDotDPerp;

    result.x = p1.x + t * bx;
    result.y = p1.y + t * by;
    return true;
}

bool Vector2::LineSegmentIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& result)
{
    float bx = p2.x - p1.x;
    float by = p2.y - p1.y;
    float dx = p4.x - p3.x;
    float dy = p4.y - p3.y;
    float bDotDPerp = bx * dy - by * dx;
    if (bDotDPerp == 0)
    {
        return false;
    }
    float cx = p3.x - p1.x;
    float cy = p3.y - p1.y;
    float t = (cx * dy - cy * dx) / bDotDPerp;
    if (t < 0 || t > 1)
    {
        return false;
    }
    float u = (cx * by - cy * bx) / bDotDPerp;
    if (u < 0 || u > 1)
    {
        return false;
    }

    result.x = p1.x + t * bx;
    result.y = p1.y + t * by;
    return true;
}

Vector2 Vector2::operator+(const Vector2 b) const
{
	return Vector2{x + b.x, y + b.y};
}

Vector2 Vector2::operator-(const Vector2 b) const
{
	return {x - b.x, y - b.y};
}

Vector2 Vector2::operator*(const Vector2 b) const
{
	return {x * b.x, y * b.y};
}

Vector2 Vector2::operator/(const Vector2 b) const
{
	return {x / b.x, y / b.y};
}

Vector2 Vector2::operator-() const
{
	return {-x, -y};
}

Vector2 Vector2::operator*(const float d) const
{
	return {x * d, y * d};
}

Vector2 Vector2::operator/(float d) const
{
	return {x / d, y / d};
}

bool Vector2::operator==(Vector2 rhs) const
{
	// Returns false in the presence of NaN values.
	float diff_x = x - rhs.x;
	float diff_y = y - rhs.y;
	return (diff_x * diff_x + diff_y * diff_y) < Math::kEpsilon * Math::kEpsilon;
}

bool Vector2::operator!=(Vector2 rhs) const
{
	// Returns true in the presence of NaN values.
	return !(*this == rhs);
}
