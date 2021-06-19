//
// Created by 董宸 on 2021/6/19.
//

#ifndef SOURCE_VECTOR3_H
#define SOURCE_VECTOR3_H


class Vector3 {

public:

    static const Vector3 zeroVector;
    static const Vector3 oneVector;
    static const Vector3 upVector;
    static const Vector3 downVector;
    static const Vector3 leftVector;
    static const Vector3 rightVector;
    static const Vector3 forwardVector;
    static const Vector3 backVector;
    static const Vector3 positiveInfinityVector;
    static const Vector3 negativeInfinityVector;
	
	Vector3() : x(0), y(0) , z(0) {}

	Vector3(float x, float y) : x(x), y(y), z(0) {}

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3(class Vector2 vec2);
	
    // X component of the vector.
    float x;
    // Y component of the vector.
    float y;
    // Z component of the vector.
    float z;

    // Linearly interpolates between two vectors.
	static Vector3 Lerp(Vector3 a, Vector3 b, float t);

    // Linearly interpolates between two vectors without clamping the interpolant
	static Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);

    // Moves a point /current/ in a straight line towards a /target/ point.
	static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta);

	static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, 
        float smoothTime, float maxSpeed);

	static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, 
        float smoothTime);

    // Gradually changes a vector towards a desired goal over time.
	static Vector3 SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, 
        float smoothTime, float maxSpeed, float deltaTime);

    // Access the x, y, z components using [0], [1], [2] respectively.
	float& operator[](int index);

    // Set x, y and z components of an existing Vector3.
    void Set(float newX, float newY, float newZ) { x = newX; y = newY; z = newZ; }

    // Multiplies two vectors component-wise.
    static Vector3 Scale(Vector3 a, Vector3 b);

    // Multiplies every component of this vector by the same component of /scale/.
    void Scale(Vector3 scale);

    // Cross Product of two vectors.
    static Vector3 Cross(Vector3 lhs, Vector3 rhs);

    // used to allow Vector3s to be used as keys in hash tables
    // public override int GetHashCode()
    // {
    //     return x.GetHashCode() ^ (y.GetHashCode() << 2) ^ (z.GetHashCode() >> 2);
    // }

    // also required for being able to use Vector3s as keys in hash tables
    // public override bool Equals(object other)
    // {
    //     if (!(other is Vector3)) return false;
    //
    //     return Equals((Vector3)other);
    // }
    //
    // public bool Equals(Vector3 other)
    // {
    //     return x == other.x && y == other.y && z == other.z;
    // }

    // Reflects a vector off the plane defined by a normal.
	static Vector3 Reflect(Vector3 inDirection, Vector3 inNormal);

    // *undoc* --- we have normalized property now
	static Vector3 Normalize(Vector3 value);

    // Makes this vector have a ::ref::magnitude of 1.
	void Normalize();

    // Returns this vector with a ::ref::magnitude of 1 (RO).
	Vector3 normalized();

        // Dot Product of two vectors.
	static float Dot(Vector3 lhs, Vector3 rhs);

    // Projects a vector onto another vector.
	static Vector3 Project(Vector3 vector, Vector3 onNormal);

    // Projects a vector onto a plane defined by a normal orthogonal to the plane.
	static Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);

    // Returns the angle in degrees between /from/ and /to/. This is always the smallest
	static float Angle(Vector3 from, Vector3 to);

    // The smaller of the two possible angles between the two vectors is returned, therefore the result will never be greater than 180 degrees or smaller than -180 degrees.
    // If you imagine the from and to vectors as lines on a piece of paper, both originating from the same point, then the /axis/ vector would point up out of the paper.
    // The measured angle between the two vectors would be positive in a clockwise direction and negative in an anti-clockwise direction.
	static float SignedAngle(Vector3 from, Vector3 to, Vector3 axis);

    // Returns the distance between /a/ and /b/.
	static float Distance(Vector3 a, Vector3 b);

    // Returns a copy of /vector/ with its magnitude clamped to /maxLength/.
	static Vector3 ClampMagnitude(Vector3 vector, float maxLength);

    // *undoc* --- there's a property now
	static float Magnitude(Vector3 vector);

    // Returns the length of this vector (RO).
	float magnitude();

    // *undoc* --- there's a property now
	static float SqrMagnitude(Vector3 vector);

    // Returns the squared length of this vector (RO).
	float sqrMagnitude();

        // Returns a vector that is made from the smallest components of two vectors.
	static Vector3 Min(Vector3 lhs, Vector3 rhs);

    // Returns a vector that is made from the largest components of two vectors.
	static Vector3 Max(Vector3 lhs, Vector3 rhs);


        // Adds two vectors.
    Vector3 operator+(Vector3 b) const;
    // Subtracts one vector from another.
    Vector3 operator-(Vector3 b) const;
    // Negates a vector.
    Vector3 operator-() const;
    // Multiplies a vector by a number.
    Vector3 operator*(float d) const;
    // Divides a vector by a number.
    Vector3 operator/(float d) const;

    // Returns true if the vectors are equal.
    bool operator==(Vector3 rhs) const;

    // Returns true if vectors are different.
    bool operator!=(Vector3 rhs) const
    {
        // Returns true in the presence of NaN values.
        return !(*this == rhs);
    }

    // public override string ToString()
    // {
    //     return ToString(null, CultureInfo.InvariantCulture.NumberFormat);
    // }
    //
    // public string ToString(string format)
    // {
    //     return ToString(format, CultureInfo.InvariantCulture.NumberFormat);
    // }
    //
    // public string ToString(string format, IFormatProvider formatProvider)
    // {
    //     if (string.IsNullOrEmpty(format))
    //         format = "F1";
    //     return String.Format("({0}, {1}, {2})", x.ToString(format, formatProvider), y.ToString(format, formatProvider), z.ToString(format, formatProvider));
    // }

    static Vector3 fwd(){ return {0.F, 0.F, 1.F}; }

	static float AngleBetween(Vector3 from, Vector3 to);

	static Vector3 Exclude(Vector3 excludeThis, Vector3 fromThat);
};


#endif //SOURCE_VECTOR3_H
