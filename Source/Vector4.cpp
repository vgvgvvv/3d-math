//
// Created by 董宸 on 2021/6/19.
//

#include "Vector4.h"
#include "Utility.h"

const Vector4 Vector4::zeroVector(0.F, 0.F, 0.F, 0.F);
const Vector4 Vector4::oneVector(1.F, 1.F, 1.F, 1.F);
const Vector4 Vector4::positiveInfinityVector = Vector4(FLOAT_INFINITY, FLOAT_INFINITY,
	FLOAT_INFINITY, FLOAT_INFINITY);
const Vector4 Vector4::negativeInfinityVector = Vector4(-FLOAT_INFINITY, -FLOAT_INFINITY,
	-FLOAT_INFINITY, -FLOAT_INFINITY);

float& Vector4::operator[](int index)
{
	ASSERT(index == 0 || index == 1 || index == 2 || index == 3, "Vector4 index is error!!");

	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		break;
	}
	return x;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 0.F;
}

Vector4::Vector4(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.F;
	this->w = 0.F;
}

void Vector4::Set(float newX, float newY, float newZ, float newW)
{
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
{
	t = Math::Clamp01(t);
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.w + (b.w - a.w) * t
	};
}

Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
{
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.w + (b.w - a.w) * t
	};
}

Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target, float maxDistanceDelta)
{
	float toVector_x = target.x - current.x;
	float toVector_y = target.y - current.y;
	float toVector_z = target.z - current.z;
	float toVector_w = target.w - current.w;

	float sqdist = (toVector_x * toVector_x +
		toVector_y * toVector_y +
		toVector_z * toVector_z +
		toVector_w * toVector_w);

	if (sqdist == 0 || (maxDistanceDelta >= 0 && sqdist <= maxDistanceDelta * maxDistanceDelta))
		return target;

	auto dist = (float)Math::Sqrt(sqdist);

	return {
		current.x + toVector_x / dist * maxDistanceDelta,
	               current.y + toVector_y / dist * maxDistanceDelta,
	               current.z + toVector_z / dist * maxDistanceDelta,
	               current.w + toVector_w / dist * maxDistanceDelta
	};
}

Vector4 Vector4::Scale(Vector4 a, Vector4 b)
{
	return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

void Vector4::Scale(Vector4 scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	w *= scale.w;
}

Vector4 Vector4::Normalize(Vector4 a)
{
	float mag = Magnitude(a);
	if (mag > Math::kEpsilon)
		return a / mag;
	else
		return zeroVector;
}

void Vector4::Normalize()
{
	float mag = Magnitude(*this);
	if (mag > Math::kEpsilon)
	{
		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
	else
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
}

Vector4 Vector4::normalized()
{
	return Vector4::Normalize(*this);
}

float Vector4::Dot(Vector4 a, Vector4 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 Vector4::Project(Vector4 a, Vector4 b)
{
	return b * (Dot(a, b) / Dot(b, b));
}

float Vector4::Distance(Vector4 a, Vector4 b)
{
	return Magnitude(a - b);
}

float Vector4::Magnitude(Vector4 a)
{
	return (float)Math::Sqrt(Dot(a, a));
}

float Vector4::magnitude()
{
	return (float)Math::Sqrt(Dot(*this, *this));
}

float Vector4::sqrMagnitude()
{
	return Dot(*this, *this);
}

Vector4 Vector4::Min(Vector4 lhs, Vector4 rhs)
{
	return {Math::Min(lhs.x, rhs.x), Math::Min(lhs.y, rhs.y), Math::Min(lhs.z, rhs.z), Math::Min(lhs.w, rhs.w)};
}

Vector4 Vector4::Max(Vector4 lhs, Vector4 rhs)
{
	return {Math::Max(lhs.x, rhs.x), Math::Max(lhs.y, rhs.y), Math::Max(lhs.z, rhs.z), Math::Max(lhs.w, rhs.w)};
}

Vector4 Vector4::operator+(Vector4 b) const
{
	return Vector4(x + x, y + b.y, z + b.z, w + b.w);
}

Vector4 Vector4::operator-(Vector4 b) const
{
	return Vector4(x - b.x, y - b.y, z - b.z, w - b.w);
}

Vector4 Vector4::operator-() const
{
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator*(float d) const
{
	return Vector4(x * d, y * d, z * d, w * d);
}

Vector4 Vector4::operator/(float d) const
{
	return Vector4(x / d, y / d, z / d, w / d);
}

bool Vector4::operator==(Vector4 rhs) const
{
	// Returns false in the presence of NaN values.
	float diffx = x - rhs.x;
	float diffy = y - rhs.y;
	float diffz = z - rhs.z;
	float diffw = w - rhs.w;
	float sqrmag = diffx * diffx + diffy * diffy + diffz * diffz + diffw * diffw;
	return sqrmag < Math::kEpsilon * Math::kEpsilon;
}

float Vector4::SqrMagnitude(Vector4 a)
{
	return Vector4::Dot(a, a);
}

float Vector4::SqrMagnitude()
{
	return Dot(*this, *this);
}
