//
// Created by 董宸 on 2021/6/19.
//
#pragma once


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
    static float Dot(Vector2 lhs, Vector2 rhs);

    // Returns the length of this vector (RO).
    float magnitude();

    // Returns the squared length of this vector (RO).
    float sqrMagnitude();

    // Returns the angle in degrees between /from/ and /to/.
    static float Angle(Vector2 from, Vector2 to);

    // Returns the signed angle in degrees between /from/ and /to/. Always returns the smallest possible angle
    static float SignedAngle(Vector2 from, Vector2 to);

    // Returns the distance between /a/ and /b/.
    static float Distance(Vector2 a, Vector2 b);

    // Returns a copy of /vector/ with its magnitude clamped to /maxLength/.
    static Vector2 ClampMagnitude(Vector2 vector, float maxLength);

    // [Obsolete("Use Vector2.sqrMagnitude")]
    static float SqrMagnitude(Vector2 a);
    // [Obsolete("Use Vector2.sqrMagnitude")]
    float SqrMagnitude();

    // Returns a vector that is made from the smallest components of two vectors.
    static Vector2 Min(Vector2 lhs, Vector2 rhs);

    // Returns a vector that is made from the largest components of two vectors.
    static Vector2 Max(Vector2 lhs, Vector2 rhs);

    static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime, float maxSpeed);

    static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime);

    static Vector2 SmoothDamp(Vector2 current, Vector2 target, Vector2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

    // Infinite Line Intersection (line1 is p1-p2 and line2 is p3-p4)
    static bool LineIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& result);

    static bool LineSegmentIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& result);

    // Adds two vectors.
    Vector2 operator+( Vector2 b) const;
    // Subtracts one vector from another.
    Vector2 operator-( Vector2 b) const;
    // Multiplies one vector by another.
    Vector2 operator*( Vector2 b) const;
    // Divides one vector over another.
    Vector2 operator/( Vector2 b) const;
    // Negates a vector.
    Vector2 operator-() const;
    // Multiplies a vector by a number.
    Vector2 operator*( float d) const;
    // Divides a vector by a number.
    Vector2 operator/(float d) const;
    // Returns true if the vectors are equal.
    bool operator==(Vector2 rhs) const;

    // Returns true if vectors are different.
    bool operator!=(Vector2 rhs) const;
};

