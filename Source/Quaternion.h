//
// Created by 董宸 on 2021/6/19.
//

#pragma once

class Vector3;
class Matrix3x3;
class Matrix4x4;

class Quaternion {

public:
    // X component of the Quaternion. Don't modify this directly unless you know quaternions inside out.
    float x;
    // Y component of the Quaternion. Don't modify this directly unless you know quaternions inside out.
    float y;
    // Z component of the Quaternion. Don't modify this directly unless you know quaternions inside out.
    float z;
    // W component of the Quaternion. Don't modify this directly unless you know quaternions inside out.
    float w;

    static const Quaternion identityQuaternion;

    float& operator[](int index);

    Quaternion();
    // Constructs new Quaternion with given x,y,z,w components.
    Quaternion(float x, float y, float z, float w);

    // Set x, y, z and w components of an existing Quaternion.
    void Set(float newX, float newY, float newZ, float newW);

    

    // The identity rotation (RO). This quaternion corresponds to "no rotation": the object
    static Quaternion identity();

    // Combines rotations /lhs/ and /rhs/.
    Quaternion operator*(Quaternion rhs) const;

        // Rotates the point /point/ with /rotation/.
    Vector3 operator*(Vector3 point) const;

private:
    // Is the dot product of two quaternions within tolerance for them to be considered equal?
    static bool IsEqualUsingDot(float dot);

public:
    // Are two quaternions equal to each other?
    bool operator==(Quaternion rhs) const;

    // Are two quaternions different from each other?
    bool operator!=(Quaternion rhs) const;

    // The dot product between two rotations.
    static float Dot(Quaternion a, Quaternion b);

    void SetLookRotation(Vector3 view);

    // Creates a rotation with the specified /forward/ and /upwards/ directions.
    void SetLookRotation(Vector3 view, Vector3 up);

    // Returns the angle in degrees between two rotations /a/ and /b/.
    static float Angle(Quaternion a, Quaternion b);

private:
    // Makes euler angles positive 0/360 with 0.0001 hacked to support old behaviour of QuaternionToEuler
    static Vector3 Internal_MakePositive(Vector3 euler);

public:

    Vector3 GetEulerAngle() const;

    void SetEulerAngle(Vector3 value);


    static Quaternion Euler(float x, float y, float z);

    static Quaternion Euler(Vector3 euler);

    void ToAngleAxis(float& angle, Vector3& axis) const;

    void SetFromToRotation(Vector3 fromDirection, Vector3 toDirection);

    static Quaternion Normalize(Quaternion q);

    void Normalize();

    Quaternion normalized() const;

        // used to allow Quaternions to be used as keys in hash tables
    //     override int GetHashCode()
    // {
    //     return x.GetHashCode() ^ (y.GetHashCode() << 2) ^ (z.GetHashCode() >> 2) ^ (w.GetHashCode() >> 1);
    // }
    //
    // // also required for being able to use Quaternions as keys in hash tables
    // override bool Equals(object other)
    // {
    //     if (!(other is Quaternion)) return false;
    //
    //     return Equals((Quaternion)other);
    // }
    //
    // bool Equals(Quaternion other)
    // {
    //     return x.Equals(other.x) && y.Equals(other.y) && z.Equals(other.z) && w.Equals(other.w);
    // }

    // override string ToString()
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

    static Quaternion FromToRotation(Vector3 fromDirection, Vector3 toDirection);

    static Quaternion Inverse(Quaternion rotation);

    Quaternion Conjugate() const;

    static Quaternion Slerp(Quaternion q1, Quaternion q2, float t);


    static Quaternion Lerp(Quaternion q1, Quaternion q2, float t);


private:

    static Quaternion Internal_FromEulerRad(Vector3 euler);

    static Vector3 Internal_ToEulerRad(Quaternion rotation);

public:

    static Quaternion FromMatrix3x3(Matrix3x3 m);

    static Matrix3x3 ToMatrix3x3(Quaternion rotation);

    static Quaternion FromMatrix4x4(Matrix4x4 m);

    static Matrix4x4 ToMatrix4x4(Quaternion rotation);

private:
    static void Internal_ToAxisAngleRad(Quaternion q, Vector3& axis, float& targetAngle);

public:
    static Quaternion AngleAxis(float angle, Vector3 axis);

    static Quaternion LookRotation(Vector3 forward, Vector3 upwards);
    static Quaternion LookRotation(Vector3 forward);
};

