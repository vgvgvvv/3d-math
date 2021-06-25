//
// Created by 董宸 on 2021/6/19.
//

#include "Vector3.h"

#include "Vector2.h"
#include "Utility.h"
#include "MathTime.h"

const Vector3 Vector3::zeroVector(0.F, 0.F, 0.F);
const Vector3 Vector3::oneVector(1.F, 1.F, 1.F);
const Vector3 Vector3::upVector(0.F, 1.F, 0.F);
const Vector3 Vector3::downVector(0.F, -1.F, 0.F);
const Vector3 Vector3::leftVector(-1.F, 0.F, 0.F);
const Vector3 Vector3::rightVector(1.F, 0.F, 0.F);
const Vector3 Vector3::forwardVector(0.F, 0.F, 1.F);
const Vector3 Vector3::backVector(0.F, 0.F, -1.F);
const Vector3 Vector3::positiveInfinityVector(FLOAT_INFINITY, FLOAT_INFINITY, FLOAT_INFINITY);
const Vector3 Vector3::negativeInfinityVector(-FLOAT_INFINITY, -FLOAT_INFINITY, -FLOAT_INFINITY);

Vector3::Vector3(Vector2 vec2)
{
	x = vec2.x;
	y = vec2.y;
	z = 0;
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
{
	t = Math::Clamp01(t);
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	};
}

Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t)
{
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	};
}

Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta)
{
	// avoid vector ops because current scripting backends are terrible at inlining
	const float toVector_x = target.x - current.x;
	const float toVector_y = target.y - current.y;
	const float toVector_z = target.z - current.z;

	const float sqdist = toVector_x * toVector_x + toVector_y * toVector_y + toVector_z * toVector_z;

	if (sqdist == 0 || (maxDistanceDelta >= 0 && sqdist <= maxDistanceDelta * maxDistanceDelta))
		return target;
	const auto dist = static_cast<float>(Math::Sqrt(sqdist));

	return {
		current.x + toVector_x / dist * maxDistanceDelta,
	               current.y + toVector_y / dist * maxDistanceDelta,
	               current.z + toVector_z / dist * maxDistanceDelta
	};
}

Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, float smoothTime, float maxSpeed)
{
	float deltaTime = Time::deltaTime;
	return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, float smoothTime)
{
	float deltaTime = Time::deltaTime;
	float maxSpeed = Math::Infinity;
	return SmoothDamp(current, target, currentVelocity, smoothTime, maxSpeed, deltaTime);
}

Vector3 Vector3::SmoothDamp(Vector3 current, Vector3 target, Vector3& currentVelocity, 
	float smoothTime, float maxSpeed, float deltaTime)
{
	float output_x = 0.f;
	float output_y = 0.f;
	float output_z = 0.f;

	// Based on Game Programming Gems 4 Chapter 1.10
	smoothTime = Math::Max(0.0001F, smoothTime);
	float omega = 2.f / smoothTime;

	float x = omega * deltaTime;
	float exp = 1.f / (1.f + x + 0.48F * x * x + 0.235F * x * x * x);

	float change_x = current.x - target.x;
	float change_y = current.y - target.y;
	float change_z = current.z - target.z;
	Vector3 originalTo = target;

	// Clamp maximum speed
	float maxChange = maxSpeed * smoothTime;

	float maxChangeSq = maxChange * maxChange;
	float sqrmag = change_x * change_x + change_y * change_y + change_z * change_z;
	if (sqrmag > maxChangeSq)
	{
		auto mag = (float)Math::Sqrt(sqrmag);
		change_x = change_x / mag * maxChange;
		change_y = change_y / mag * maxChange;
		change_z = change_z / mag * maxChange;
	}

	target.x = current.x - change_x;
	target.y = current.y - change_y;
	target.z = current.z - change_z;

	float temp_x = (currentVelocity.x + omega * change_x) * deltaTime;
	float temp_y = (currentVelocity.y + omega * change_y) * deltaTime;
	float temp_z = (currentVelocity.z + omega * change_z) * deltaTime;

	currentVelocity.x = (currentVelocity.x - omega * temp_x) * exp;
	currentVelocity.y = (currentVelocity.y - omega * temp_y) * exp;
	currentVelocity.z = (currentVelocity.z - omega * temp_z) * exp;

	output_x = target.x + (change_x + temp_x) * exp;
	output_y = target.y + (change_y + temp_y) * exp;
	output_z = target.z + (change_z + temp_z) * exp;

	// Prevent overshooting
	float origMinusCurrent_x = originalTo.x - current.x;
	float origMinusCurrent_y = originalTo.y - current.y;
	float origMinusCurrent_z = originalTo.z - current.z;
	float outMinusOrig_x = output_x - originalTo.x;
	float outMinusOrig_y = output_y - originalTo.y;
	float outMinusOrig_z = output_z - originalTo.z;

	if (origMinusCurrent_x * outMinusOrig_x + origMinusCurrent_y * outMinusOrig_y + origMinusCurrent_z * outMinusOrig_z
		> 0)
	{
		output_x = originalTo.x;
		output_y = originalTo.y;
		output_z = originalTo.z;

		currentVelocity.x = (output_x - originalTo.x) / deltaTime;
		currentVelocity.y = (output_y - originalTo.y) / deltaTime;
		currentVelocity.z = (output_z - originalTo.z) / deltaTime;
	}

	return {output_x, output_y, output_z};
}

float& Vector3::operator[](int index)
{
	ASSERT(index == 0 || index == 1 || index == 2, "Vector3 index is error");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default:
			break;
	}
	return x;
}

Vector3 Vector3::Scale(Vector3 a, Vector3 b)
{
	return {a.x * b.x, a.y * b.y, a.z * b.z};
}

void Vector3::Scale(Vector3 scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
{
	return {
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	};
}

Vector3 Vector3::Reflect(Vector3 inDirection, Vector3 inNormal)
{
	float factor = -2.F * Dot(inNormal, inDirection);
	return {
		factor * inNormal.x + inDirection.x,
	               factor * inNormal.y + inDirection.y,
	               factor * inNormal.z + inDirection.z
	};
}

Vector3 Vector3::Normalize(Vector3 value)
{
	float mag = Magnitude(value);
	if (mag > Math::kEpsilon)
		return value / mag;
	else
		return zeroVector;
}

void Vector3::Normalize()
{
	float mag = Magnitude(*this);
	if (mag > Math::kEpsilon)
	{
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
	else
	{
		x = 0;
		y = 0;
		z = 0;
	}
}

Vector3 Vector3::normalized()
{
	return Normalize(*this);
}

float Vector3::Dot(Vector3 lhs, Vector3 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Project(Vector3 vector, Vector3 onNormal)
{
	float sqrMag = Dot(onNormal, onNormal);
	if (sqrMag < Math::Epsilon)
		return zeroVector;
	else
	{
		auto dot = Dot(vector, onNormal);
		return {
			onNormal.x * dot / sqrMag,
			onNormal.y * dot / sqrMag,
			onNormal.z * dot / sqrMag
		};
	}
}

Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
{
	float sqrMag = Dot(planeNormal, planeNormal);
	if (sqrMag < Math::Epsilon)
		return vector;
	else
	{
		auto dot = Dot(vector, planeNormal);
		return Vector3(vector.x - planeNormal.x * dot / sqrMag,
		               vector.y - planeNormal.y * dot / sqrMag,
		               vector.z - planeNormal.z * dot / sqrMag);
	}
}

float Vector3::Angle(Vector3 from, Vector3 to)
{
	// sqrt(a) * sqrt(b) = sqrt(a * b) -- valid for real numbers
	float denominator = (float)Math::Sqrt(from.sqrMagnitude() * to.sqrMagnitude());
	if (denominator < Math::kEpsilonNormalSqrt)
		return 0.F;

	float dot = Math::Clamp(Dot(from, to) / denominator, -1.F, 1.F);
	return ((float)Math::Acos(dot)) * Math::Rad2Deg;
}

float Vector3::SignedAngle(Vector3 from, Vector3 to, Vector3 axis)
{
	float unsignedAngle = Angle(from, to);

	float cross_x = from.y * to.z - from.z * to.y;
	float cross_y = from.z * to.x - from.x * to.z;
	float cross_z = from.x * to.y - from.y * to.x;
	float sign = Math::Sign(axis.x * cross_x + axis.y * cross_y + axis.z * cross_z);
	return unsignedAngle * sign;
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
	float diff_x = a.x - b.x;
	float diff_y = a.y - b.y;
	float diff_z = a.z - b.z;
	return (float)Math::Sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
}

Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
{
	float sqrmag = vector.sqrMagnitude();
	if (sqrmag > maxLength * maxLength)
	{
		float mag = (float)Math::Sqrt(sqrmag);
		//these intermediate variables force the intermediate result to be
		//of float precision. without this, the intermediate result can be of higher
		//precision, which changes behavior.
		float normalized_x = vector.x / mag;
		float normalized_y = vector.y / mag;
		float normalized_z = vector.z / mag;
		return Vector3(normalized_x * maxLength,
		               normalized_y * maxLength,
		               normalized_z * maxLength);
	}
	return vector;
}

float Vector3::Magnitude(Vector3 vector)
{
	return (float)Math::Sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

float Vector3::magnitude()
{
	return (float)Math::Sqrt(x * x + y * y + z * z);
}

float Vector3::SqrMagnitude(Vector3 vector)
{
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
}

float Vector3::sqrMagnitude()
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::Min(Vector3 lhs, Vector3 rhs)
{
	return {Math::Min(lhs.x, rhs.x), Math::Min(lhs.y, rhs.y), Math::Min(lhs.z, rhs.z)};
}

Vector3 Vector3::Max(Vector3 lhs, Vector3 rhs)
{
	return {Math::Max(lhs.x, rhs.x), Math::Max(lhs.y, rhs.y), Math::Max(lhs.z, rhs.z)};
}

Vector3 Vector3::operator+(Vector3 b) const
{
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(Vector3 b) const
{
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float d) const
{
	return Vector3(x * d, y * d, z * d);
}

Vector3 Vector3::operator/(float d) const
{
	return Vector3(x / d, y / d, z / d);
}

bool Vector3::operator==(Vector3 rhs) const
{
	// Returns false in the presence of NaN values.
	float diff_x = x - rhs.x;
	float diff_y = y - rhs.y;
	float diff_z = z - rhs.z;
	float sqrmag = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;
	return sqrmag < Math::kEpsilon * Math::kEpsilon;
}

float Vector3::AngleBetween(Vector3 from, Vector3 to)
{
	return (float)Math::Acos(Math::Clamp(Vector3::Dot(from.normalized(), to.normalized()), -1.F, 1.F));
}

Vector3 Vector3::Exclude(Vector3 excludeThis, Vector3 fromThat)
{
	return ProjectOnPlane(fromThat, excludeThis);
}
