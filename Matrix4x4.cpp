//
// Created by 董宸 on 2021/6/19.
//

#include "Matrix4x4.h"

const Matrix4x4 Matrix4x4::zeroMatrix = Matrix4x4(
	Vector4(0, 0, 0, 0),
	Vector4(0, 0, 0, 0),
	Vector4(0, 0, 0, 0),
	Vector4(0, 0, 0, 0));

const Matrix4x4 Matrix4x4::identityMatrix = Matrix4x4(
	Vector4(1, 0, 0, 0),
	Vector4(0, 1, 0, 0),
	Vector4(0, 0, 1, 0),
	Vector4(0, 0, 0, 1));

Matrix4x4::Matrix4x4()
{
	this->m00 = 0;
	this->m01 = 0;
	this->m02 = 0;
	this->m03 = 0;
	this->m10 = 0;
	this->m11 = 0;
	this->m12 = 0;
	this->m13 = 0;
	this->m20 = 0;
	this->m21 = 0;
	this->m22 = 0;
	this->m23 = 0;
	this->m30 = 0;
	this->m31 = 0;
	this->m32 = 0;
	this->m33 = 0;
}

Matrix4x4::Matrix4x4(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3)
{
	this->m00 = column0.x;
	this->m01 = column1.x;
	this->m02 = column2.x;
	this->m03 = column3.x;
	this->m10 = column0.y;
	this->m11 = column1.y;
	this->m12 = column2.y;
	this->m13 = column3.y;
	this->m20 = column0.z;
	this->m21 = column1.z;
	this->m22 = column2.z;
	this->m23 = column3.z;
	this->m30 = column0.w;
	this->m31 = column1.w;
	this->m32 = column2.w;
	this->m33 = column3.w;
}

Matrix4x4::Matrix4x4(
	float m00, float m01, float m02, float m03, 
	float m10, float m11, float m12, float m13, 
	float m20, float m21, float m22, float m23, 
	float m30, float m31, float m32, float m33)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	this->m03 = m03;
	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;
	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;
	this->m30 = m30;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

float Matrix4x4::Get(int row, int column) const
{
	return Get(row + column * 4);
}

void Matrix4x4::Set(int row, int column, float value)
{
	Set(row + column * 4, value);
}


void Matrix4x4::Set(Matrix4x4 mat)
{
	this->m00 = mat.m00;
	this->m01 = mat.m01;
	this->m02 = mat.m02;
	this->m03 = mat.m03;
	this->m10 = mat.m10;
	this->m11 = mat.m11;
	this->m12 = mat.m12;
	this->m13 = mat.m13;
	this->m20 = mat.m20;
	this->m21 = mat.m21;
	this->m22 = mat.m22;
	this->m23 = mat.m23;
	this->m30 = mat.m30;
	this->m31 = mat.m31;
	this->m32 = mat.m32;
	this->m33 = mat.m33;
}

float Matrix4x4::Get(int index) const
{
	ASSERT(index >= 0 && index <= 15, "Matrix4x4 index is error!!");

	switch (index)
	{
	case 0: return m00;
	case 1: return m10;
	case 2: return m20;
	case 3: return m30;
	case 4: return m01;
	case 5: return m11;
	case 6: return m21;
	case 7: return m31;
	case 8: return m02;
	case 9: return m12;
	case 10: return m22;
	case 11: return m32;
	case 12: return m03;
	case 13: return m13;
	case 14: return m23;
	case 15: return m33;
	default: ;
	}
	return m00;
}

void Matrix4x4::Set(int index, float value)
{
	ASSERT(index >= 0 && index <= 15, "Matrix4x4 index is error!!");

	switch (index)
	{
	case 0: m00 = value;
		break;
	case 1: m10 = value;
		break;
	case 2: m20 = value;
		break;
	case 3: m30 = value;
		break;
	case 4: m01 = value;
		break;
	case 5: m11 = value;
		break;
	case 6: m21 = value;
		break;
	case 7: m31 = value;
		break;
	case 8: m02 = value;
		break;
	case 9: m12 = value;
		break;
	case 10: m22 = value;
		break;
	case 11: m32 = value;
		break;
	case 12: m03 = value;
		break;
	case 13: m13 = value;
		break;
	case 14: m23 = value;
		break;
	case 15: m33 = value;
		break;
	default: ;
	}
}

float& Matrix4x4::operator[](int index)
{
	ASSERT(index >= 0 && index <= 15, "Matrix4x4 index is error!!");

	switch (index)
	{
	case 0: return m00;
	case 1: return m10;
	case 2: return m20;
	case 3: return m30;
	case 4: return m01;
	case 5: return m11;
	case 6: return m21;
	case 7: return m31;
	case 8: return m02;
	case 9: return m12;
	case 10: return m22;
	case 11: return m32;
	case 12: return m03;
	case 13: return m13;
	case 14: return m23;
	case 15: return m33;
	default: ;
	}
	return m00;
}

Matrix4x4 Matrix4x4::operator*(Matrix4x4 rhs) const
{
	Matrix4x4 res;
	res.m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20 + m03 * rhs.m30;
	res.m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21 + m03 * rhs.m31;
	res.m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22 + m03 * rhs.m32;
	res.m03 = m00 * rhs.m03 + m01 * rhs.m13 + m02 * rhs.m23 + m03 * rhs.m33;

	res.m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20 + m13 * rhs.m30;
	res.m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
	res.m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
	res.m13 = m10 * rhs.m03 + m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;

	res.m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20 + m23 * rhs.m30;
	res.m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31;
	res.m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32;
	res.m23 = m20 * rhs.m03 + m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33;

	res.m30 = m30 * rhs.m00 + m31 * rhs.m10 + m32 * rhs.m20 + m33 * rhs.m30;
	res.m31 = m30 * rhs.m01 + m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31;
	res.m32 = m30 * rhs.m02 + m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32;
	res.m33 = m30 * rhs.m03 + m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33;

	return res;
}

Vector4 Matrix4x4::operator*(Vector4 vector) const
{
	Vector4 res;
	res.x = m00 * vector.x + m01 * vector.y + m02 * vector.z + m03 * vector.w;
	res.y = m10 * vector.x + m11 * vector.y + m12 * vector.z + m13 * vector.w;
	res.z = m20 * vector.x + m21 * vector.y + m22 * vector.z + m23 * vector.w;
	res.w = m30 * vector.x + m31 * vector.y + m32 * vector.z + m33 * vector.w;
	return res;
}

bool Matrix4x4::operator==(Matrix4x4 rhs) const
{
	// Returns false in the presence of NaN values.
	return GetColumn(0) == rhs.GetColumn(0)
		&& GetColumn(1) == rhs.GetColumn(1)
		&& GetColumn(2) == rhs.GetColumn(2)
		&& GetColumn(3) == rhs.GetColumn(3);
}

bool Matrix4x4::operator!=(Matrix4x4 rhs) const
{
	// Returns true in the presence of NaN values.
	return !(*this == rhs);
}

Vector4 Matrix4x4::GetColumn(int index) const
{
	switch (index)
	{
	case 0: return {m00, m10, m20, m30};
	case 1: return {m01, m11, m21, m31};
	case 2: return {m02, m12, m22, m32};
	case 3: return {m03, m13, m23, m33};
	default: ;
	}
	return Vector4::zeroVector;
}

Vector4 Matrix4x4::GetRow(int index)
{
	switch (index)
	{
	case 0: return {m00, m01, m02, m03};
	case 1: return {m10, m11, m12, m13};
	case 2: return {m20, m21, m22, m23};
	case 3: return {m30, m31, m32, m33};
	default: ;
	}
}

void Matrix4x4::SetColumn(int index, Vector4 column)
{
	Set(0, index, column.x);
	Set(1, index, column.y);
	Set(2, index, column.z);
	Set(3, index, column.w);
}

void Matrix4x4::SetRow(int index, Vector4 row)
{
	Set(index, 0, row.x);
	Set(index, 1, row.y);
	Set(index, 2, row.z);
	Set(index, 3, row.w);
}

Vector3 Matrix4x4::MultiplyPoint(Vector3 point) const
{
	Vector3 res;
	float w;
	res.x = this->m00 * point.x + this->m01 * point.y + this->m02 * point.z + this->m03;
	res.y = this->m10 * point.x + this->m11 * point.y + this->m12 * point.z + this->m13;
	res.z = this->m20 * point.x + this->m21 * point.y + this->m22 * point.z + this->m23;
	w = this->m30 * point.x + this->m31 * point.y + this->m32 * point.z + this->m33;

	w = 1.0F / w;
	res.x *= w;
	res.y *= w;
	res.z *= w;
	return res;
}

Vector3 Matrix4x4::MultiplyPoint3x4(Vector3 point) const
{
	Vector3 res;
	res.x = this->m00 * point.x + this->m01 * point.y + this->m02 * point.z + this->m03;
	res.y = this->m10 * point.x + this->m11 * point.y + this->m12 * point.z + this->m13;
	res.z = this->m20 * point.x + this->m21 * point.y + this->m22 * point.z + this->m23;
	return res;
}

Vector3 Matrix4x4::MultiplyVector(Vector3 vector) const
{
	Vector3 res;
	res.x = this->m00 * vector.x + this->m01 * vector.y + this->m02 * vector.z;
	res.y = this->m10 * vector.x + this->m11 * vector.y + this->m12 * vector.z;
	res.z = this->m20 * vector.x + this->m21 * vector.y + this->m22 * vector.z;
	return res;
}

Plane Matrix4x4::TransformPlane(Plane plane)
{
	auto ittrans = this->inverse();

	float x = plane.GetNormal().x, y = plane.GetNormal().y, z = plane.GetNormal().z, w = plane.GetDistance();
	// note: a transpose is part of this transformation
	auto a = ittrans.m00 * x + ittrans.m10 * y + ittrans.m20 * z + ittrans.m30 * w;
	auto b = ittrans.m01 * x + ittrans.m11 * y + ittrans.m21 * z + ittrans.m31 * w;
	auto c = ittrans.m02 * x + ittrans.m12 * y + ittrans.m22 * z + ittrans.m32 * w;
	auto d = ittrans.m03 * x + ittrans.m13 * y + ittrans.m23 * z + ittrans.m33 * w;

	return Plane(Vector3(a, b, c), d);
}

Matrix4x4 Matrix4x4::Scale(Vector3 vector)
{
	Matrix4x4 m;
	m.m00 = vector.x;
	m.m01 = 0.0F;
	m.m02 = 0.0F;
	m.m03 = 0.0F;
	m.m10 = 0.0F;
	m.m11 = vector.y;
	m.m12 = 0.0F;
	m.m13 = 0.0F;
	m.m20 = 0.0F;
	m.m21 = 0.0F;
	m.m22 = vector.z;
	m.m23 = 0.0F;
	m.m30 = 0.0F;
	m.m31 = 0.0F;
	m.m32 = 0.0F;
	m.m33 = 1.0F;
	return m;
}

Matrix4x4 Matrix4x4::Translate(Vector3 vector)
{
	Matrix4x4 m;
	m.m00 = 1.0F;
	m.m01 = 0.0F;
	m.m02 = 0.0F;
	m.m03 = vector.x;
	m.m10 = 0.0F;
	m.m11 = 1.0F;
	m.m12 = 0.0F;
	m.m13 = vector.y;
	m.m20 = 0.0F;
	m.m21 = 0.0F;
	m.m22 = 1.0F;
	m.m23 = vector.z;
	m.m30 = 0.0F;
	m.m31 = 0.0F;
	m.m32 = 0.0F;
	m.m33 = 1.0F;
	return m;
}

Matrix4x4 Matrix4x4::Rotate(Quaternion q)
{
	// Precalculate coordinate products
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

	// Calculate 3x3 matrix from orthonormal basis
	Matrix4x4 m;
	m.m00 = 1.0F - (yy + zz);
	m.m10 = xy + wz;
	m.m20 = xz - wy;
	m.m30 = 0.0F;
	m.m01 = xy - wz;
	m.m11 = 1.0F - (xx + zz);
	m.m21 = yz + wx;
	m.m31 = 0.0F;
	m.m02 = xz + wy;
	m.m12 = yz - wx;
	m.m22 = 1.0F - (xx + yy);
	m.m32 = 0.0F;
	m.m03 = 0.0F;
	m.m13 = 0.0F;
	m.m23 = 0.0F;
	m.m33 = 1.0F;
	return m;
}

bool Matrix4x4::IsIdentity() const
{
	if (Math::Approximately(Get(0, 0), 1.0F) &&
		Math::Approximately(Get(0, 1), 0.0F) &&
		Math::Approximately(Get(0, 2), 0.0F) &&
		Math::Approximately(Get(0, 3), 0.0F) &&
		Math::Approximately(Get(1, 0), 0.0F) &&
		Math::Approximately(Get(1, 1), 1.0F) &&
		Math::Approximately(Get(1, 2), 0.0F) &&
		Math::Approximately(Get(1, 3), 0.0F) &&
		Math::Approximately(Get(2, 0), 0.0F) &&
		Math::Approximately(Get(2, 1), 0.0F) &&
		Math::Approximately(Get(2, 2), 1.0F) &&
		Math::Approximately(Get(2, 3), 0.0F) &&
		Math::Approximately(Get(3, 0), 0.0F) &&
		Math::Approximately(Get(3, 1), 0.0F) &&
		Math::Approximately(Get(3, 2), 0.0F) &&
		Math::Approximately(Get(3, 3), 1.0F))
		return true;
	return false;
}

float Matrix4x4::GetDeterminant() const
{
	float m00 = Get(0, 0);
	float m01 = Get(0, 1);
	float m02 = Get(0, 2);
	float m03 = Get(0, 3);

	float m10 = Get(1, 0);
	float m11 = Get(1, 1);
	float m12 = Get(1, 2);
	float m13 = Get(1, 3);

	float m20 = Get(2, 0);
	float m21 = Get(2, 1);
	float m22 = Get(2, 2);
	float m23 = Get(2, 3);

	float m30 = Get(3, 0);
	float m31 = Get(3, 1);
	float m32 = Get(3, 2);
	float m33 = Get(3, 3);

	float result =
		m03 * m12 * m21 * m30 - m02 * m13 * m21 * m30 - m03 * m11 * m22 * m30 + m01 * m13 * m22 * m30 +
		m02 * m11 * m23 * m30 - m01 * m12 * m23 * m30 - m03 * m12 * m20 * m31 + m02 * m13 * m20 * m31 +
		m03 * m10 * m22 * m31 - m00 * m13 * m22 * m31 - m02 * m10 * m23 * m31 + m00 * m12 * m23 * m31 +
		m03 * m11 * m20 * m32 - m01 * m13 * m20 * m32 - m03 * m10 * m21 * m32 + m00 * m13 * m21 * m32 +
		m01 * m10 * m23 * m32 - m00 * m11 * m23 * m32 - m02 * m11 * m20 * m33 + m01 * m12 * m20 * m33 +
		m02 * m10 * m21 * m33 - m00 * m12 * m21 * m33 - m01 * m10 * m22 * m33 + m00 * m11 * m22 * m33;
	return result;
}


Matrix4x4 Matrix4x4::TRS(Vector3 pos, Quaternion q, Vector3 s)
{
	auto mat = Quaternion::ToMatrix4x4(q);

	mat[0] *= s[0];
	mat[1] *= s[0];
	mat[2] *= s[0];

	mat[4] *= s[1];
	mat[5] *= s[1];
	mat[6] *= s[1];

	mat[8] *= s[2];
	mat[9] *= s[2];
	mat[10] *= s[2];

	mat[12] = pos[0];
	mat[13] = pos[1];
	mat[14] = pos[2];

	return mat;
}

void Matrix4x4::SetTRS(Vector3 pos, Quaternion q, Vector3 s)
{
	Set(Matrix4x4::TRS(pos, q, s));
}

Matrix4x4 Matrix4x4::Inverse(Matrix4x4 m)
{
	auto out = m;

	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float r0[] = {
		wtmp[0][0], wtmp[0][1], wtmp[0][2], wtmp[0][3],
		wtmp[0][4], wtmp[0][5], wtmp[0][6], wtmp[0][7]
	};
	float r1[] = {
		wtmp[1][0], wtmp[1][1], wtmp[1][2], wtmp[1][3],
		wtmp[1][4], wtmp[1][5], wtmp[1][6], wtmp[1][7]
	};
	float r2[] = {
		wtmp[2][0], wtmp[2][1], wtmp[2][2], wtmp[2][3],
		wtmp[2][4], wtmp[2][5], wtmp[2][6], wtmp[2][7]
	};
	float r3[] = {
		wtmp[3][0], wtmp[3][1], wtmp[3][2], wtmp[3][3],
		wtmp[3][4], wtmp[3][5], wtmp[3][6], wtmp[3][7]
	};

	r0[0] = m.Get(0, 0);
	r0[1] = m.Get(0, 1);
	r0[2] = m.Get(0, 2);
	r0[3] = m.Get(0, 3);
	r0[4] = 1.0F;
	r0[5] = r0[6] = r0[7] = 0.0F;

	r1[0] = m.Get(1, 0);
	r1[1] = m.Get(1, 1);
	r1[2] = m.Get(1, 2);
	r1[3] = m.Get(1, 3);
	r1[5] = 1.0F;
	r1[4] = r1[6] = r1[7] = 0.0F;

	r2[0] = m.Get(2, 0);
	r2[1] = m.Get(2, 1);
	r2[2] = m.Get(2, 2);
	r2[3] = m.Get(2, 3);
	r2[6] = 1.0F;
	r2[4] = r2[5] = r2[7] = 0.0F;

	r3[0] = m.Get(3, 0);
	r3[1] = m.Get(3, 1);
	r3[2] = m.Get(3, 2);
	r3[3] = m.Get(3, 3);
	r3[7] = 1.0F;
	r3[4] = r3[5] = r3[6] = 0.0F;

	/* choose pivot - or die */
	if (Math::Abs(r3[0]) > Math::Abs(r2[0])) Swap(r3, r2);
	if (Math::Abs(r2[0]) > Math::Abs(r1[0])) Swap(r2, r1);
	if (Math::Abs(r1[0]) > Math::Abs(r0[0])) Swap(r1, r0);
	if (0.0F == r0[0]) return identityMatrix;

	/* eliminate first autoiable     */
	m1 = r1[0] / r0[0];
	m2 = r2[0] / r0[0];
	m3 = r3[0] / r0[0];
	s = r0[1];
	r1[1] -= m1 * s;
	r2[1] -= m2 * s;
	r3[1] -= m3 * s;
	s = r0[2];
	r1[2] -= m1 * s;
	r2[2] -= m2 * s;
	r3[2] -= m3 * s;
	s = r0[3];
	r1[3] -= m1 * s;
	r2[3] -= m2 * s;
	r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0F)
	{
		r1[4] -= m1 * s;
		r2[4] -= m2 * s;
		r3[4] -= m3 * s;
	}
	s = r0[5];
	if (s != 0.0F)
	{
		r1[5] -= m1 * s;
		r2[5] -= m2 * s;
		r3[5] -= m3 * s;
	}
	s = r0[6];
	if (s != 0.0F)
	{
		r1[6] -= m1 * s;
		r2[6] -= m2 * s;
		r3[6] -= m3 * s;
	}
	s = r0[7];
	if (s != 0.0F)
	{
		r1[7] -= m1 * s;
		r2[7] -= m2 * s;
		r3[7] -= m3 * s;
	}

	/* choose pivot - or die */
	if (Math::Abs(r3[1]) > Math::Abs(r2[1])) Swap(r3, r2);
	if (Math::Abs(r2[1]) > Math::Abs(r1[1])) Swap(r2, r1);
	if (0.0F == r1[1]) return zeroMatrix;

	/* eliminate second autoiable */
	m2 = r2[1] / r1[1];
	m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2];
	r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3];
	r3[3] -= m3 * r1[3];
	s = r1[4];
	if (0.0F != s)
	{
		r2[4] -= m2 * s;
		r3[4] -= m3 * s;
	}
	s = r1[5];
	if (0.0F != s)
	{
		r2[5] -= m2 * s;
		r3[5] -= m3 * s;
	}
	s = r1[6];
	if (0.0F != s)
	{
		r2[6] -= m2 * s;
		r3[6] -= m3 * s;
	}
	s = r1[7];
	if (0.0F != s)
	{
		r2[7] -= m2 * s;
		r3[7] -= m3 * s;
	}

	/* choose pivot - or die */
	if (Math::Abs(r3[2]) > Math::Abs(r2[2])) Swap(r3, r2);
	if (0.0F == r2[2]) return zeroMatrix;

	/* eliminate third autoiable */
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3];
	r3[4] -= m3 * r2[4];
	r3[5] -= m3 * r2[5];
	r3[6] -= m3 * r2[6];
	r3[7] -= m3 * r2[7];

	/* last check */
	if (0.0F == r3[3]) return zeroMatrix;

	s = 1.0F / r3[3]; /* now back substitute row 3 */
	r3[4] *= s;
	r3[5] *= s;
	r3[6] *= s;
	r3[7] *= s;

	m2 = r2[3]; /* now back substitute row 2 */
	s = 1.0F / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2);
	r2[5] = s * (r2[5] - r3[5] * m2);
	r2[6] = s * (r2[6] - r3[6] * m2);
	r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1;
	r1[5] -= r3[5] * m1;
	r1[6] -= r3[6] * m1;
	r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0;
	r0[5] -= r3[5] * m0;
	r0[6] -= r3[6] * m0;
	r0[7] -= r3[7] * m0;

	m1 = r1[2]; /* now back substitute row 1 */
	s = 1.0F / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1);
	r1[5] = s * (r1[5] - r2[5] * m1);
	r1[6] = s * (r1[6] - r2[6] * m1);
	r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0;
	r0[5] -= r2[5] * m0;
	r0[6] -= r2[6] * m0;
	r0[7] -= r2[7] * m0;

	m0 = r0[1]; /* now back substitute row 0 */
	s = 1.0F / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0);
	r0[5] = s * (r0[5] - r1[5] * m0);
	r0[6] = s * (r0[6] - r1[6] * m0);
	r0[7] = s * (r0[7] - r1[7] * m0);

	out.Set(0, 0, r0[4]);
	out.Set(0, 1, r0[5]);
	out.Set(0, 2, r0[6]);
	out.Set(0, 3, r0[7]);
	out.Set(1, 0, r1[4]);
	out.Set(1, 1, r1[5]);
	out.Set(1, 2, r1[6]);
	out.Set(1, 3, r1[7]);
	out.Set(2, 0, r2[4]);
	out.Set(2, 1, r2[5]);
	out.Set(2, 2, r2[6]);
	out.Set(2, 3, r2[7]);
	out.Set(3, 0, r3[4]);
	out.Set(3, 1, r3[5]);
	out.Set(3, 2, r3[6]);
	out.Set(3, 3, r3[7]);

	return out;
}

Matrix4x4 Matrix4x4::Transpose(Matrix4x4 m)
{
	auto res = m;
	Swap(m.m01, m.m10);
	Swap(m.m02, m.m20);
	Swap(m.m03, m.m30);
	Swap(m.m12, m.m21);
	Swap(m.m13, m.m31);
	Swap(m.m23, m.m32);
	return res;
}

Matrix4x4 Matrix4x4::transpose() const
{
	return Matrix4x4::Transpose(*this);
}

Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	auto mat = Matrix4x4::identityMatrix;

	float deltax = right - left;
	float deltay = top - bottom;
	float deltaz = zFar - zNear;

	mat.m00 = 2.0F / deltax;
	mat.m03 = -(right + left) / deltax;
	mat.m11 = 2.0F / deltay;
	mat.m13 = -(top + bottom) / deltay;
	mat.m22 = -2.0F / deltaz;
	mat.m23 = -(zFar + zNear) / deltaz;
	return mat;
}

Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar)
{
	auto mat = Matrix4x4::identityMatrix;
	float cotangent, deltaZ;
	float radians = fov / 2.0F * Math::Deg2Rad;
	cotangent = Math::Cos(radians) / Math::Sin(radians);
	deltaZ = zNear - zFar;

	mat.Set(0, 0, cotangent / aspect);
	mat.Set(0, 1, 0.0F);
	mat.Set(0, 2, 0.0F);
	mat.Set(0, 3, 0.0F);
	mat.Set(1, 0, 0.0F);
	mat.Set(1, 1, cotangent);
	mat.Set(1, 2, 0.0F);
	mat.Set(1, 3, 0.0F);
	mat.Set(2, 0, 0.0F);
	mat.Set(2, 1, 0.0F);
	mat.Set(2, 2, (zFar + zNear) / deltaZ);
	mat.Set(2, 3, 2.0F * zNear * zFar / deltaZ);
	mat.Set(3, 0, 0.0F);
	mat.Set(3, 1, 0.0F);
	mat.Set(3, 2, -1.0F);
	mat.Set(3, 3, 0.0F);

	return mat;
}

Matrix4x4 Matrix4x4::Frustum(float left, float right, float bottom, float top, float nearval, float farval)
{
	auto mat = Matrix4x4::identityMatrix;
	float x, y, a, b, c, d, e;

	x = (2.0F * nearval) / (right - left);
	y = (2.0F * nearval) / (top - bottom);
	a = (right + left) / (right - left);
	b = (top + bottom) / (top - bottom);
	c = -(farval + nearval) / (farval - nearval);
	d = -(2.0F * farval * nearval) / (farval - nearval);
	e = -1.0F;

	mat.m00 = x;
	mat.m01 = 0.0F;
	mat.m02 = a;
	mat.m03 = 0.0F;
	mat.m10 = 0.0F;
	mat.m11 = y;
	mat.m12 = b;
	mat.m13 = 0.0F;
	mat.m20 = 0.0F;
	mat.m21 = 0.0F;
	mat.m22 = c;
	mat.m23 = d;
	mat.m30 = 0.0F;
	mat.m31 = 0.0F;
	mat.m32 = e;
	mat.m33 = 0.0F;
	return mat;
}

Matrix4x4 Matrix4x4::Frustum1(const FrustumPlanes& fp)
{
	return Matrix4x4::Frustum(fp.left, fp.right, fp.bottom, fp.top, fp.zNear, fp.zFar);
}