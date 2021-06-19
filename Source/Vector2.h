//
// Created by 董宸 on 2021/6/19.
//

#ifndef SOURCE_VECTOR2_H
#define SOURCE_VECTOR2_H

#include <string>
#include "MathFuncs.h"
#include "Vector3.h"

class Vector2 {
public:
    float x;
    float y;

    static const Vector2 zeroVector;
    static const Vector2 oneVector;
    static const Vector2 upVector;
    static const Vector2 downVector;
    static const Vector2 leftVector;
    static const Vector2 rightVector;
    static const Vector2 positiveInfinityVector;
    static const Vector2 negativeInfinityVector;

    static const float kEpsilon;
    static const float kEpsilonNormalSqrt;

    float& operator[] (int index);

    // Constructs a new vector with given x, y components.
    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }

    // Converts a [[Vector3]] to a Vector2.
//    Vector2(Vector3 v)
//    {
//        this->x = v.x;
//        this->y = v.y;
//    }

    // Set x and y components of an existing Vector2.
    void Set(float newX, float newY) { x = newX; y = newY; }

    // Linearly interpolates between two vectors.
    static Vector2 Lerp(Vector2 a, Vector2 b, float t);

    // Linearly interpolates between two vectors without clamping the interpolant
    static Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);

    // Moves a point /current/ towards /target/.
    static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);

    // Multiplies two vectors component-wise.
    static Vector2 Scale(Vector2 a, Vector2 b) { return Vector2(a.x * b.x, a.y * b.y); }

    // Multiplies every component of this vector by the same component of /scale/.
    void Scale(Vector2 scale) { x *= scale.x; y *= scale.y; }

    // Makes this vector have a ::ref::magnitude of 1.
    void Normalize();

    // Returns this vector with a ::ref::magnitude of 1 (RO).
    Vector2 normalized();

    /// *listonly*
    /*std::string ToString()
    {
        return ToString(null, CultureInfo.InvariantCulture.NumberFormat);
    }

    // Returns a nicely formatted string for this vector.
    std::string ToString(std::string format)
    {
        return ToString(format, CultureInfo.InvariantCulture.NumberFormat);
    }

    std::string ToString(std::string format, IFormatProvider formatProvider)
    {
        if (string.IsNullOrEmpty(format))
            format = "F1";
        return String.Format("({0}, {1})", x.ToString(format, formatProvider), y.ToString(format, formatProvider));
    }

    // used to allow Vector2s to be used as keys in hash tables
public override int GetHashCode()
    {
        return x.GetHashCode() ^ (y.GetHashCode() << 2);
    }

    // also required for being able to use Vector2s as keys in hash tables
public override bool Equals(object other)
    {
        if (!(other is Vector2)) return false;

        return Equals((Vector2)other);
    }

public bool Equals(Vector2 other)
    {
        return x == other.x && y == other.y;
    }*/

    static Vector2 Reflect(Vector2 inDirection, Vector2 inNormal);

    static Vector2 Perpendicular(Vector2 inDirection);

    // Dot Product of two vectors.
    static float Dot(Vector2 lhs, Vector2 rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

    // Returns the length of this vector (RO).
    float magnitude() {  return (float)Math::Sqrt(x * x + y * y);  }

    // Returns the squared length of this vector (RO).
    float sqrMagnitude() { return x * x + y * y; }

    // Returns the angle in degrees between /from/ and /to/.
    static float Angle(Vector2 from, Vector2 to);

    // Returns the signed angle in degrees between /from/ and /to/. Always returns the smallest possible angle
    static float SignedAngle(Vector2 from, Vector2 to);

    // Returns the distance between /a/ and /b/.
    static float Distance(Vector2 a, Vector2 b);

    // Returns a copy of /vector/ with its magnitude clamped to /maxLength/.
    static Vector2 ClampMagnitude(Vector2 vector, float maxLength);

    // [Obsolete("Use Vector2.sqrMagnitude")]
    static float SqrMagnitude(Vector2 a) { return a.x * a.x + a.y * a.y; }
    // [Obsolete("Use Vector2.sqrMagnitude")]
    float SqrMagnitude() { return x * x + y * y; }

    // Returns a vector that is made from the smallest components of two vectors.
    static Vector2 Min(Vector2 lhs, Vector2 rhs) { return Vector2(Math::Min(lhs.x, rhs.x), Math::Min(lhs.y, rhs.y)); }

    // Returns a vector that is made from the largest components of two vectors.
    static Vector2 Max(Vector2 lhs, Vector2 rhs) { return Vector2(Math::Max(lhs.x, rhs.x), Math::Max(lhs.y, rhs.y)); }

    static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime, float maxSpeed);

    static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime);

    static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

    // Infinite Line Intersection (line1 is p1-p2 and line2 is p3-p4)
    static bool LineIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& result);

    static bool LineSegmentIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& result);

    // Adds two vectors.
    Vector2 operator+(const Vector2 b) const { return Vector2{x + b.x, y + b.y}; }
    // Subtracts one vector from another.
    Vector2 operator-(const Vector2 b) const { return Vector2{x - b.x, y - b.y}; }
    // Multiplies one vector by another.
    Vector2 operator*(const Vector2 b) const { return Vector2{x * b.x, y * b.y}; }
    // Divides one vector over another.
    Vector2 operator/(const Vector2 b) const { return Vector2{x / b.x, y / b.y}; }
    // Negates a vector.
    Vector2 operator-() const { return Vector2{-x, -y}; }
    // Multiplies a vector by a number.
    Vector2 operator*(const float d) const { return Vector2{x * d, y * d}; }
    // Divides a vector by a number.
    Vector2 operator/(float d) const { return Vector2(x / d, y / d); }
    // Returns true if the vectors are equal.
    bool operator==(Vector2 rhs) const
    {
        // Returns false in the presence of NaN values.
        float diff_x = x - rhs.x;
        float diff_y = y - rhs.y;
        return (diff_x * diff_x + diff_y * diff_y) < kEpsilon * kEpsilon;
    }

    // Returns true if vectors are different.
    bool operator!=(Vector2 rhs) const
    {
        // Returns true in the presence of NaN values.
        return !(*this == rhs);
    }

};

#endif //SOURCE_VECTOR2_H
