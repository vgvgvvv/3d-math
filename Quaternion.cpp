//
// Created by 董宸 on 2021/6/19.
//

#include "Quaternion.h"


#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Utility.h"
#include "Vector3.h"

const Quaternion Quaternion::identityQuaternion = Quaternion(0.0F, 0.0F, 0.0F, 1.0F);


float& Quaternion::operator[](int index)
{
	ASSERT(index >= 0 && index <= 3, "Quaternion index is error!!");
	switch (index)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		;
	}
	return x;
}

Quaternion::Quaternion()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Quaternion::Set(float newX, float newY, float newZ, float newW)
{
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

Quaternion Quaternion::identity()
{
	return identityQuaternion;
}

Quaternion Quaternion::operator*(Quaternion rhs) const
{
	return {
		w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
		w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
		w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
		w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
	};
}

Vector3 Quaternion::operator*(Vector3 point) const
{
	float x = this->x * 2.0F;
	float y = this->y * 2.0F;
	float z = this->z * 2.0F;
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;

	Vector3 res;
	res.x = (1.0F - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	res.y = (xy + wz) * point.x + (1.0F - (xx + zz)) * point.y + (yz - wx) * point.z;
	res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0F - (xx + yy)) * point.z;
	return res;
}

bool Quaternion::IsEqualUsingDot(float dot)
{
	// Returns false in the presence of NaN values.
	return dot > 1.0f - Math::kEpsilon;
}

bool Quaternion::operator==(Quaternion rhs) const
{
	return IsEqualUsingDot(Dot(*this, rhs));
}

bool Quaternion::operator!=(Quaternion rhs) const
{
	// Returns true in the presence of NaN values.
	return !(*this == rhs);
}

float Quaternion::Dot(Quaternion a, Quaternion b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

void Quaternion::SetLookRotation(Vector3 view)
{
	Vector3 up = Vector3::upVector;
	SetLookRotation(view, up);
}

void Quaternion::SetLookRotation(Vector3 view, Vector3 up)
{
	*this = LookRotation(view, up);
}

float Quaternion::Angle(Quaternion a, Quaternion b)
{
	float dot = Dot(a, b);
	return IsEqualUsingDot(dot) ? 0.0f : Math::Acos(Math::Min(Math::Abs(dot), 1.0F)) * 2.0F * Math::Rad2Deg;
}

Vector3 Quaternion::Internal_MakePositive(Vector3 euler)
{
	float negativeFlip = -0.0001f * Math::Rad2Deg;
	float positiveFlip = 360.0f + negativeFlip;

	if (euler.x < negativeFlip)
		euler.x += 360.0f;
	else if (euler.x > positiveFlip)
		euler.x -= 360.0f;

	if (euler.y < negativeFlip)
		euler.y += 360.0f;
	else if (euler.y > positiveFlip)
		euler.y -= 360.0f;

	if (euler.z < negativeFlip)
		euler.z += 360.0f;
	else if (euler.z > positiveFlip)
		euler.z -= 360.0f;

	return euler;
}

Vector3 Quaternion::GetEulerAngle() const
{
	return Internal_MakePositive(Internal_ToEulerRad(*this) * Math::Rad2Deg);
}

void Quaternion::SetEulerAngle(Vector3 value)
{
	auto q = Internal_FromEulerRad(value * Math::Deg2Rad);
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion Quaternion::Euler(float x, float y, float z)
{
	return Internal_FromEulerRad(Vector3(x, y, z) * Math::Deg2Rad);
}

Quaternion Quaternion::Euler(Vector3 euler)
{
	return Internal_FromEulerRad(euler * Math::Deg2Rad);
}

void Quaternion::ToAngleAxis(float& angle, Vector3& axis) const
{
	Internal_ToAxisAngleRad(*this, axis, angle);
	angle *= Math::Rad2Deg;
}

void Quaternion::SetFromToRotation(Vector3 fromDirection, Vector3 toDirection)
{
	auto q = FromToRotation(fromDirection, toDirection);
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion Quaternion::Normalize(Quaternion q)
{
	float mag = Math::Sqrt(Dot(q, q));

	if (mag < Math::Epsilon)
		return Quaternion::identity();

	return Quaternion(q.x / mag, q.y / mag, q.z / mag, q.w / mag);
}

void Quaternion::Normalize()
{
	auto q = Normalize(*this);
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion Quaternion::normalized() const
{
	return Normalize(*this);
}

Quaternion Quaternion::FromToRotation(Vector3 fromDirection, Vector3 toDirection)
{
	auto lhs = fromDirection;
	auto rhs = toDirection;
	float lhsMag = Vector3::Magnitude(lhs);
	float rhsMag = Vector3::Magnitude(rhs);
	if (lhsMag < Math::kEpsilon || rhsMag < Math::kEpsilon)
	{
		return Quaternion::identity();
	}
	else
	{
		auto from = lhs / lhsMag;
		auto to = rhs / rhsMag;
		auto m = Matrix3x3::FromToRotation(from, to);
		auto q = FromMatrix3x3(m);
		return q;
	}
}

Quaternion Quaternion::Inverse(Quaternion rotation)
{
	return rotation.Conjugate();
}

Quaternion Quaternion::Conjugate() const
{
	return {-x, -y, -z, w};
}

Quaternion Quaternion::Slerp(Quaternion q1, Quaternion q2, float t)
{
	//	Quaternionf q3 = new Quaternionf();
	float dot = Dot(q1, q2);

	// dot = cos(theta)
	// if (dot < 0), q1 and q2 are more than 90 degrees apart,
	// so we can invert one to reduce spinning
	Quaternion tmpQuat;
	if (dot < 0.0f)
	{
		dot = -dot;
		tmpQuat.Set(-q2.x,
		            -q2.y,
		            -q2.z,
		            -q2.w);
	}
	else
		tmpQuat = q2;


	if (dot < 0.95f)
	{
		float angle = Math::Acos(dot);
		float sinadiv, sinat, sinaomt;
		sinadiv = 1.0f / Math::Sin(angle);
		sinat = Math::Sin(angle * t);
		sinaomt = Math::Sin(angle * (1.0f - t));
		tmpQuat.Set((q1.x * sinaomt + tmpQuat.x * sinat) * sinadiv,
		            (q1.y * sinaomt + tmpQuat.y * sinat) * sinadiv,
		            (q1.z * sinaomt + tmpQuat.z * sinat) * sinadiv,
		            (q1.w * sinaomt + tmpQuat.w * sinat) * sinadiv);
		// AssertIf (!CompareApproximately (SqrMagnitude (tmpQuat), 1.0F));
		return tmpQuat;
	}
		// if the angle is small, use linear interpolation
	else
	{
		return Lerp(q1, tmpQuat, t);
	}
}

Quaternion Quaternion::Lerp(Quaternion q1, Quaternion q2, float t)
{
	Quaternion tmpQuat;
	// if (dot < 0), q1 and q2 are more than 360 deg apart.
	// The problem is that quaternions are 720deg of freedom.
	// so we - all components when lerping
	if (Dot(q1, q2) < 0.0F)
	{
		tmpQuat.Set(q1.x + t * (-q2.x - q1.x),
		            q1.y + t * (-q2.y - q1.y),
		            q1.z + t * (-q2.z - q1.z),
		            q1.w + t * (-q2.w - q1.w));
	}
	else
	{
		tmpQuat.Set(q1.x + t * (q2.x - q1.x),
		            q1.y + t * (q2.y - q1.y),
		            q1.z + t * (q2.z - q1.z),
		            q1.w + t * (q2.w - q1.w));
	}
	return Normalize(tmpQuat);
}

Quaternion Quaternion::Internal_FromEulerRad(Vector3 euler)
{
	float cX = Math::Cos(euler.x / 2.0f);
	float sX = Math::Sin(euler.x / 2.0f);

	float cY = Math::Cos(euler.y / 2.0f);
	float sY = Math::Sin(euler.y / 2.0f);

	float cZ = Math::Cos(euler.z / 2.0f);
	float sZ = Math::Sin(euler.z / 2.0f);

	Quaternion qX(sX, 0.0F, 0.0F, cX);
	Quaternion qY(0.0F, sY, 0.0F, cY);
	Quaternion qZ(0.0F, 0.0F, sZ, cZ);

	Quaternion q = (qY * qX) * qZ;
	// AssertIf (!CompareApproximately (SqrMagnitude (q), 1.0F));
	return q;
}

Vector3 Quaternion::Internal_ToEulerRad(Quaternion rotation)
{
	Matrix3x3 m;
	Vector3 rot;
	m = ToMatrix3x3(rotation.normalized());
	m.ToEuler(rot);
	return rot;
}

Quaternion Quaternion::FromMatrix3x3(Matrix3x3 m)
{
	auto kRot = m;
	Quaternion q;
	float fTrace = kRot.m00 + kRot.m11 + kRot.m22;
	float fRoot;

	if (fTrace > 0.0f)
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = Math::Sqrt(fTrace + 1.0f); // 2w
		q.w = 0.5f * fRoot;
		fRoot = 0.5f / fRoot; // 1/(4w)
		q.x = (kRot.m21 - kRot.m12) * fRoot;
		q.y = (kRot.m02 - kRot.m20) * fRoot;
		q.z = (kRot.m10 - kRot.m01) * fRoot;
	}
	else
	{
		// |w| <= 1/2
		int s_iNext[] = {1, 2, 0};
		int i = 0;
		if (kRot.m11 > kRot.m00)
			i = 1;
		if (kRot.m22 > kRot[i, i])
			i = 2;
		int j = s_iNext[i];
		int k = s_iNext[j];

		fRoot = Math::Sqrt(kRot[i, i] - kRot[j, j] - kRot[k, k] + 1.0f);
		float apkQuat[] = {q.x, q.y, q.z};
		// AssertIf (fRoot < Vector3.kEpsilon);
		apkQuat[i] = 0.5f * fRoot;
		fRoot = 0.5f / fRoot;
		q.w = (kRot[k, j] - kRot[j, k]) * fRoot;
		apkQuat[j] = (kRot[j, i] + kRot[i, j]) * fRoot;
		apkQuat[k] = (kRot[k, i] + kRot[i, k]) * fRoot;
	}
	q = Normalize(q);
	return q;
}

Matrix3x3 Quaternion::ToMatrix3x3(Quaternion rotation)
{
	auto q = rotation;
	float x = q.x * 2.0F;
	float y = q.y * 2.0F;
	float z = q.z * 2.0F;
	float xx = q.x * x;
	float yy = q.y * y;
	float zz = q.z * z;
	float xy = q.x * y;
	float xz = q.x * z;
	float yz = q.y * z;
	float wx = q.w * x;
	float wy = q.w * y;
	float wz = q.w * z;

	Matrix3x3 m;
	// Calculate 3x3 matrix from orthonormal basis
	m[0] = 1.0f - (yy + zz);
	m[1] = xy + wz;
	m[2] = xz - wy;

	m[3] = xy - wz;
	m[4] = 1.0f - (xx + zz);
	m[5] = yz + wx;

	m[6] = xz + wy;
	m[7] = yz - wx;
	m[8] = 1.0f - (xx + yy);

	return m;
}

Quaternion Quaternion::FromMatrix4x4(Matrix4x4 m)
{
	auto m3 = Matrix3x3(
		m.m00, m.m01, m.m02,
		m.m00, m.m01, m.m02,
		m.m00, m.m01, m.m02);
	return FromMatrix3x3(m3);
}

Matrix4x4 Quaternion::ToMatrix4x4(Quaternion rotation)
{
	auto q = rotation;
	float x = q.x * 2.0F;
	float y = q.y * 2.0F;
	float z = q.z * 2.0F;
	float xx = q.x * x;
	float yy = q.y * y;
	float zz = q.z * z;
	float xy = q.x * y;
	float xz = q.x * z;
	float yz = q.y * z;
	float wx = q.w * x;
	float wy = q.w * y;
	float wz = q.w * z;

	Matrix4x4 m;
	// Calculate 3x3 matrix from orthonormal basis
	m[0] = 1.0f - (yy + zz);
	m[1] = xy + wz;
	m[2] = xz - wy;
	m[3] = 0.0F;

	m[4] = xy - wz;
	m[5] = 1.0f - (xx + zz);
	m[6] = yz + wx;
	m[7] = 0.0F;

	m[8] = xz + wy;
	m[9] = yz - wx;
	m[10] = 1.0f - (xx + yy);
	m[11] = 0.0F;

	m[12] = 0.0F;
	m[13] = 0.0F;
	m[14] = 0.0F;
	m[15] = 1.0F;

	return m;
}

void Quaternion::Internal_ToAxisAngleRad(Quaternion q, Vector3& axis, float& targetAngle)
{
	q = q.normalized();
	//AssertIf (! CompareApproximately(SqrMagnitude (q), 1.0F));
	targetAngle = 2.0f * Math::Acos(q.w);
	if (Math::Approximately(targetAngle, 0.0F))
	{
		axis = Vector3::rightVector;
		return;
	}

	float div = 1.0f / Math::Sqrt(1.0f - q.w * q.w);
	axis = Vector3(q.x * div, q.y * div, q.z * div);
}

Quaternion Quaternion::AngleAxis(float angle, Vector3 axis)
{
	auto rad = angle * Math::Deg2Rad;
	Quaternion q;
	float mag = axis.magnitude();
	if (mag > 0.000001F)
	{
		float halfAngle = angle * 0.5F;

		q.w = Math::Cos(halfAngle);

		float s = Math::Sin(halfAngle) / mag;
		q.x = s * axis.x;
		q.y = s * axis.y;
		q.z = s * axis.z;
		return q;
	}
	else
	{
		return Quaternion::identity();
	}
}

Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 upwards)
{
	Matrix3x3 m;
	if (!Matrix3x3::LookRotationToMatrix(forward, upwards, m))
		return Quaternion::identity();
	return FromMatrix3x3(m);
}

Quaternion Quaternion::LookRotation(Vector3 forward)
{
	return LookRotation(forward, Vector3::upVector);
}
