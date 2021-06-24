//
// Created by 董宸 on 2021/6/19.
//
//
#pragma once


class Vector2;
class Vector3;

class Vector4 {
	
public:

    static const Vector4 zeroVector;
    static const Vector4 oneVector;
    static const Vector4 positiveInfinityVector;
    static const Vector4 negativeInfinityVector;

	
    // X component of the vector.
    float x;
    // Y component of the vector.
    float y;
    // Z component of the vector.
    float z;
    // W component of the vector.
    float w;

    float& operator[](int index);

    Vector4();
	
    // Creates a new vector with given x, y, z, w components.
    Vector4(float x, float y, float z, float w);
    // Creates a new vector with given x, y, z components and sets /w/ to zero.
    Vector4(float x, float y, float z);
    // Creates a new vector with given x, y components and sets /z/ and /w/ to zero.
    Vector4(float x, float y);

    Vector4(Vector3 vec3);
	
    Vector4(Vector2 vec2);
	
    // Set x, y, z and w components of an existing Vector4.
    void Set(float newX, float newY, float newZ, float newW);

    // Linearly interpolates between two vectors.
    static Vector4 Lerp(Vector4 a, Vector4 b, float t);

    // Linearly interpolates between two vectors without clamping the interpolant
    static Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);

    // Moves a point /current/ towards /target/.
    static Vector4 MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta);

    // Multiplies two vectors component-wise.
    static Vector4 Scale(Vector4 a, Vector4 b);

    // Multiplies every component of this vector by the same component of /scale/.
    void Scale(Vector4 scale);

    // // used to allow Vector4s to be used as keys in hash tables
    // int GetHashCode()
    // {
    //     return x.GetHashCode() ^ (y.GetHashCode() << 2) ^ (z.GetHashCode() >> 2) ^ (w.GetHashCode() >> 1);
    // }
    //
    // // also required for being able to use Vector4s as keys in hash tables
    // bool Equals(object other)
    // {
    //     if (!(other is Vector4)) return false;
    //
    //     return Equals((Vector4)other);
    // }
    //
    // bool Equals(Vector4 other)
    // {
    //     return x == other.x && y == other.y && z == other.z && w == other.w;
    // }

    // *undoc* --- we have normalized property now
    static Vector4 Normalize(Vector4 a);

    // Makes this vector have a ::ref::magnitude of 1.
    void Normalize();

    // Returns this vector with a ::ref::magnitude of 1 (RO).
    Vector4 normalized();

        // Dot Product of two vectors.
    static float Dot(Vector4 a, Vector4 b);

    // Projects a vector onto another vector.
    static Vector4 Project(Vector4 a, Vector4 b);

    // Returns the distance between /a/ and /b/.
    static float Distance(Vector4 a, Vector4 b);

    // *undoc* --- there's a property now
    static float Magnitude(Vector4 a);

    // Returns the length of this vector (RO).
    float magnitude();

        // Returns the squared length of this vector (RO).
    float sqrMagnitude();

        // Returns a vector that is made from the smallest components of two vectors.
    static Vector4 Min(Vector4 lhs, Vector4 rhs);

    // Returns a vector that is made from the largest components of two vectors.
    static Vector4 Max(Vector4 lhs, Vector4 rhs);

    
        // Adds two vectors.
    Vector4 operator+(Vector4 b) const;
    // Subtracts one vector from another.
    Vector4 operator-(Vector4 b) const;
    // Negates a vector.
    Vector4 operator-() const;
    // Multiplies a vector by a number.
    Vector4 operator*(float d) const;
    // Divides a vector by a number.
    Vector4 operator/(float d) const;

    // Returns true if the vectors are equal.
    bool operator==(Vector4 rhs) const;

    // Returns true if vectors are different.
    bool operator!=(Vector4 rhs)
    {
        // Returns true in the presence of NaN values.
        return !(*this == rhs);
    }

    // string ToString()
    // {
    //     return ToString(null, CultureInfo.InautoiantCulture.NumberFormat);
    // }
    //
    // string ToString(string format)
    // {
    //     return ToString(format, CultureInfo.InautoiantCulture.NumberFormat);
    // }
    //
    // string ToString(string format, IFormatProvider formatProvider)
    // {
    //     if (string.IsNullOrEmpty(format))
    //         format = "F1";
    //     return String.Format("({0}, {1}, {2}, {3})", x.ToString(format, formatProvider), y.ToString(format, formatProvider), z.ToString(format, formatProvider), w.ToString(format, formatProvider));
    // }

    // *undoc* --- there's a property now
    static float SqrMagnitude(Vector4 a);
    // *undoc* --- there's a property now
    float SqrMagnitude();
};

