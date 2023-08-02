//
// Created by 董宸 on 2021/6/19.
//

#include "Matrix3x3.h"

#include "Utility.h"
#include "Vector3.h"
#include "Vector4.h"

// Returns a matrix with all elements set to zero (RO).
const Matrix3x3 Matrix3x3::zero = Matrix3x3(
	Vector3(0, 0, 0),
	Vector3(0, 0, 0),
	Vector3(0, 0, 0));

const Matrix3x3 Matrix3x3::IdentityMatrix = Matrix3x3(
	Vector3(1, 0, 0),
	Vector3(0, 1, 0),
	Vector3(0, 0, 1));

Matrix3x3::Matrix3x3()
{
	this->m00 = 0;
	this->m01 = 0;
	this->m02 = 0;
	this->m10 = 0;
	this->m11 = 0;
	this->m12 = 0;
	this->m20 = 0;
	this->m21 = 0;
	this->m22 = 0;
}

Matrix3x3::Matrix3x3(Vector3 column0, Vector3 column1, Vector3 column2)
{
	this->m00 = column0.x;
	this->m01 = column1.x;
	this->m02 = column2.x;
	this->m10 = column0.y;
	this->m11 = column1.y;
	this->m12 = column2.y;
	this->m20 = column0.z;
	this->m21 = column1.z;
	this->m22 = column2.z;
}

Matrix3x3::Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
}

float Matrix3x3::Get(int row, int column) const
{
	return Get(row + column * 3);
}

void Matrix3x3::Set(int row, int column, float value)
{
	Set(row + column * 3, value);
}

float Matrix3x3::Get(int index) const
{
	ASSERT(index >= 0 && index <= 8, "Matrix Index is error!!");

	switch (index)
	{
	case 0: return m00;
	case 1: return m10;
	case 2: return m20;
	case 3: return m01;
	case 4: return m11;
	case 5: return m21;
	case 6: return m02;
	case 7: return m12;
	case 8: return m22;
	default:
		break;
	}
	return m00;
}

void Matrix3x3::Set(int index, float value)
{
	ASSERT(index >= 0 && index <= 8, "Matrix Index is error!!");

	switch (index)
	{
	case 0: m00 = value;
		break;
	case 1: m10 = value;
		break;
	case 2: m20 = value;
		break;
	case 3: m01 = value;
		break;
	case 4: m11 = value;
		break;
	case 5: m21 = value;
		break;
	case 6: m02 = value;
		break;
	case 7: m12 = value;
		break;
	case 8: m22 = value;
		break;
	default:
		break;
	}
}

float& Matrix3x3::operator[](int index)
{
	ASSERT(index >= 0 && index <= 8, "Matrix Index is error!!");

	switch (index)
	{
	case 0: return m00;
	case 1: return m10;
	case 2: return m20;
	case 3: return m01;
	case 4: return m11;
	case 5: return m21;
	case 6: return m02;
	case 7: return m12;
	case 8: return m22;
	default:
		break;
	}
	return m00;
}

std::vector<float> Matrix3x3::ToVector() const
{
	std::vector<float> vec;
	for (int i = 0; i < 9; i++)
	{
		vec.push_back(Get(i));
	}
	return vec;
}


Matrix3x3 Matrix3x3::operator*(Matrix3x3 rhs) const
{
	Matrix3x3 res = IdentityMatrix;
	res.m00 = m00 * rhs.m00 + m01 * rhs.m10 + m02 * rhs.m20;
	res.m01 = m00 * rhs.m01 + m01 * rhs.m11 + m02 * rhs.m21;
	res.m02 = m00 * rhs.m02 + m01 * rhs.m12 + m02 * rhs.m22;

	res.m10 = m10 * rhs.m00 + m11 * rhs.m10 + m12 * rhs.m20;
	res.m11 = m10 * rhs.m01 + m11 * rhs.m11 + m12 * rhs.m21;
	res.m12 = m10 * rhs.m02 + m11 * rhs.m12 + m12 * rhs.m22;

	res.m20 = m20 * rhs.m00 + m21 * rhs.m10 + m22 * rhs.m20;
	res.m21 = m20 * rhs.m01 + m21 * rhs.m11 + m22 * rhs.m21;
	res.m22 = m20 * rhs.m02 + m21 * rhs.m12 + m22 * rhs.m22;

	return res;
}

Vector4 Matrix3x3::operator*(Vector3 vector) const
{
	Vector3 res;
	res.x = m00 * vector.x + m01 * vector.y + m02 * vector.z;
	res.y = m10 * vector.x + m11 * vector.y + m12 * vector.z;
	res.z = m20 * vector.x + m21 * vector.y + m22 * vector.z;
	return res;
}

bool Matrix3x3::operator==(Matrix3x3 rhs) const
{
	// Returns false in the presence of NaN values.
	return GetColumn(0) == rhs.GetColumn(0)
		&& GetColumn(1) == rhs.GetColumn(1)
		&& GetColumn(2) == rhs.GetColumn(2)
		&& GetColumn(3) == rhs.GetColumn(3);
}

bool Matrix3x3::operator!=(Matrix3x3 rhs) const
{
	// Returns true in the presence of NaN values.
	return !(*this == rhs);
}

Vector3 Matrix3x3::GetColumn(int index) const
{
	ASSERT(index >= 0 && index <= 2, "Matrix3x3 Column index is error!!");
	switch (index)
	{
	case 0: return {m00, m10, m20};
	case 1: return {m01, m11, m21};
	case 2: return {m02, m12, m22};
	default: ;
	}
	return Vector3::zeroVector;
}

Vector3 Matrix3x3::GetRow(int index) const
{
	ASSERT(index >= 0 && index <= 2, "Matrix3x3 Row index is error!!");
	switch (index)
	{
	case 0: return {m00, m01, m02};
	case 1: return {m10, m11, m12};
	case 2: return {m20, m21, m22};
	default: ;
	}
	return Vector3::zeroVector;
}

void Matrix3x3::SetColumn(int index, Vector3 column)
{
	Set(0, index, column.x);
	Set(1, index, column.y);
	Set(2, index, column.z);
}

void Matrix3x3::SetRow(int index, Vector3 row)
{
	Set(index, 0, row.x);
	Set(index, 1, row.y);
	Set(index, 2, row.z);
}

Vector3 Matrix3x3::MultiplyVector(Vector3 vector) const
{
	Vector3 res;
	res.x = this->m00 * vector.x + this->m01 * vector.y + this->m02 * vector.z;
	res.y = this->m10 * vector.x + this->m11 * vector.y + this->m12 * vector.z;
	res.z = this->m20 * vector.x + this->m21 * vector.y + this->m22 * vector.z;
	return res;
}

Matrix3x3 Matrix3x3::FromEuler(Vector3 v)
{
	float cx = Math::Cos(v.x);
	float sx = Math::Sin(v.x);
	float cy = Math::Cos(v.y);
	float sy = Math::Sin(v.y);
	float cz = Math::Cos(v.z);
	float sz = Math::Sin(v.z);

	Matrix3x3 matrix;
	matrix.Set(0, 0, cy * cz + sx * sy * sz);
	matrix.Set(0, 1, cz * sx * sy - cy * sz);
	matrix.Set(0, 2, cx * sy);

	matrix.Set(1, 0, cx * sz);
	matrix.Set(1, 1, cx * cz);
	matrix.Set(1, 2, -sx);

	matrix.Set(2, 0, -cz * sy + cy * sx * sz);
	matrix.Set(2, 1, cy * cz * sx + sy * sz);
	matrix.Set(2, 2, cx * cy);

	return matrix;
}

bool Matrix3x3::ToEuler(Vector3& v)
{
	// from http://www.geometrictools.com/Documentation/EulerAngles.pdf
	// YXZ order
	if (m12 < 0.999F) // some fudge for imprecision
	{
		if (m12 > -0.999F) // some fudge for imprecision
		{
			v.x = Math::Asin(-m12);
			v.y = Math::Atan(m02, m22);
			v.z = Math::Atan(m10, m11);
			SanitizeEuler(v);
			return true;
		}
		else
		{
			// WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
			v.x = Math::PI * 0.5F;
			v.y = Math::Atan(m01, m00);
			v.z = 0.0F;
			SanitizeEuler(v);

			return false;
		}
	}
	else
	{
		// WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
		v.x = -(float)Math::PI * 0.5F;
		v.y = Math::Atan(-m01, m00);
		v.z = 0.0F;
		SanitizeEuler(v);
		return false;
	}
}

void Matrix3x3::SanitizeEuler(Vector3& euler)
{
	MakePositive(euler);
	/*
	 Vector3f option0 = euler;
	 option0.x = kPI - option0.x;
	 option0.y = kPI - option0.y;
	 option0.z = kPI - option0.z;

	 MakePositive (euler);
	 MakePositive (option0);
	 if (option0.x+option0.y+option0.z < euler.x+euler.y+euler.z)
	 euler = option0;
	 */
}

void Matrix3x3::MakePositive(Vector3& euler)
{
	const float negativeFlip = -0.0001F;
	const float positiveFlip = (Math::PI * 2.0F) - 0.0001F;

	if (euler.x < negativeFlip)
		euler.x += 2.0f * Math::PI;
	else if (euler.x > positiveFlip)
		euler.x -= 2.0f * Math::PI;

	if (euler.y < negativeFlip)
		euler.y += 2.0f * Math::PI;
	else if (euler.y > positiveFlip)
		euler.y -= 2.0f * Math::PI;

	if (euler.z < negativeFlip)
		euler.z += 2.0f * Math::PI;
	else if (euler.z > positiveFlip)
		euler.z -= 2.0f * Math::PI;
}

Matrix3x3 Matrix3x3::FromToRotation(Vector3 from, Vector3 to)
{
	Matrix3x3 mtx;
	Vector3 v;
	float e, h;
	v = Vector3::Cross(from, to);
	e = Vector3::Dot(from, to);
	if (e > 1.0 - Math::Epsilon) /* "from" almost or equal to "to"-vector? */
	{
		/* return identity */
		mtx.Set(0, 0, 1.0f);
		mtx.Set(0, 1, 0.0f);
		mtx.Set(0, 2, 0.0f);
		mtx.Set(1, 0, 0.0f);
		mtx.Set(1, 1, 1.0f);
		mtx.Set(1, 2, 0.0f);
		mtx.Set(2, 0, 0.0f);
		mtx.Set(2, 1, 0.0f);
		mtx.Set(2, 2, 1.0f);
	}
	else if (e < -1.0 + Math::Epsilon) /* "from" almost or equal to negated "to"? */
	{
		Vector3 up;
		Vector3 left;
		float invlen;
		float fxx, fyy, fzz, fxy, fxz, fyz;
		float uxx, uyy, uzz, uxy, uxz, uyz;
		float lxx, lyy, lzz, lxy, lxz, lyz;
		/* left=CROSS(from, (1,0,0)) */
		left[0] = 0.0f;
		left[1] = from[2];
		left[2] = -from[1];
		if (Vector3::Dot(left, left) < Math::Epsilon) /* was left=CROSS(from,(1,0,0)) a good choice? */
		{
			/* here we now that left = CROSS(from, (1,0,0)) will be a good choice */
			left[0] = -from[2];
			left[1] = 0.0f;
			left[2] = from[0];
		}
		/* normalize "left" */
		invlen = 1.0f / Math::Sqrt(Vector3::Dot(left, left));
		left[0] *= invlen;
		left[1] *= invlen;
		left[2] *= invlen;
		up = Vector3::Cross(left, from);
		/* now we have a coordinate system, i.e., a basis;    */
		/* M=(from, up, left), and we want to rotate to:      */
		/* N=(-from, up, -left). This is done with the matrix:*/
		/* N*M^T where M^T is the transpose of M              */
		fxx = -from[0] * from[0];
		fyy = -from[1] * from[1];
		fzz = -from[2] * from[2];
		fxy = -from[0] * from[1];
		fxz = -from[0] * from[2];
		fyz = -from[1] * from[2];

		uxx = up[0] * up[0];
		uyy = up[1] * up[1];
		uzz = up[2] * up[2];
		uxy = up[0] * up[1];
		uxz = up[0] * up[2];
		uyz = up[1] * up[2];

		lxx = -left[0] * left[0];
		lyy = -left[1] * left[1];
		lzz = -left[2] * left[2];
		lxy = -left[0] * left[1];
		lxz = -left[0] * left[2];
		lyz = -left[1] * left[2];
		/* symmetric matrix */
		mtx.Set(0, 0, fxx + uxx + lxx);
		mtx.Set(0, 1, fxy + uxy + lxy);
		mtx.Set(0, 2, fxz + uxz + lxz);
		mtx.Set(1, 0, mtx.Get(0, 1));
		mtx.Set(1, 1, fyy + uyy + lyy);
		mtx.Set(1, 2, fyz + uyz + lyz);
		mtx.Set(2, 0, mtx.Get(0, 2));
		mtx.Set(2, 1, mtx.Get(1, 2));
		mtx.Set(2, 2, fzz + uzz + lzz);
	}
	else /* the most common case, unless "from"="to", or "from"=-"to" */
	{
		/* ...otherwise use this hand optimized version (9 mults less) */
		float hvx, hvz, hvxy, hvxz, hvyz;
		h = (1.0f - e) / Vector3::Dot(v, v);
		hvx = h * v[0];
		hvz = h * v[2];
		hvxy = hvx * v[1];
		hvxz = hvx * v[2];
		hvyz = hvz * v[1];
		mtx.Set(0, 0 , e + hvx * v[0]);
		mtx.Set(0, 1 , hvxy - v[2]);
		mtx.Set(0, 2 , hvxz + v[1]);
		mtx.Set(1, 0 , hvxy + v[2]);
		mtx.Set(1, 1 , e + h * v[1] * v[1]);
		mtx.Set(1, 2 , hvyz - v[0]);
		mtx.Set(2, 0 , hvxz - v[1]);
		mtx.Set(2, 1 , hvyz + v[0]);
		mtx.Set(2, 2 , e + hvz * v[2]);
	}

	return mtx;
}

bool Matrix3x3::LookRotationToMatrix(Vector3 viewVec, Vector3 upVec, Matrix3x3& m)
{
	Vector3 z = viewVec;
	// compute u0
	float mag = z.magnitude();
	if (mag < Math::kEpsilon)
	{
		m = IdentityMatrix;
		return false;
	}
	z = z / mag;

	Vector3 x = Vector3::Cross(upVec, z);
	mag = x.magnitude();
	if (mag < Math::kEpsilon)
	{
		m = IdentityMatrix;
		return false;
	}
	x = x / mag;

	Vector3 y = (Vector3::Cross(z, x));
	if (!Math::Approximately(y.sqrMagnitude(), 1.0F))
	{
		m = IdentityMatrix;
		return false;
	}

	m = Matrix3x3();
	m.SetOrthoNormalBasis(x, y, z);
	return true;
}

void Matrix3x3::SetIdentity()
{
	Set(0, 0, 1.0f);
	Set(0, 1, 0.0f);
	Set(0, 2, 0.0f);

	Set(1, 0, 0.0f);
	Set(1, 1, 1.0f);
	Set(1, 2, 0.0f);

	Set(2, 0, 0.0f);
	Set(2, 1, 0.0f);
	Set(2, 2, 1.0f);
}

void Matrix3x3::SetZero()
{
	Set(0, 0, 0.0f);
	Set(0, 1, 0.0f);
	Set(0, 2, 0.0f);

	Set(1, 0, 0.0f);
	Set(1, 1, 0.0f);
	Set(1, 2, 0.0f);

	Set(2, 0, 0.0f);
	Set(2, 1, 0.0f);
	Set(2, 2, 0.0f);
}

void Matrix3x3::SetOrthoNormalBasis(Vector3 inX, Vector3 inY, Vector3 inZ)
{
	Set(0, 0, inX[0]);
	Set(0, 1, inY[0]);
	Set(0, 2, inZ[0]);

	Set(1, 0, inX[1]);
	Set(1, 1, inY[1]);
	Set(1, 2, inZ[1]);

	Set(2, 0, inX[2]);
	Set(2, 1, inY[2]);
	Set(2, 2, inZ[2]);
}

void Matrix3x3::SetOrthoNormalBasisInverse(Vector3 inX, Vector3 inY, Vector3 inZ)
{
	Set(0, 0, inX[0]);
	Set(1, 0, inY[0]);
	Set(2, 0, inZ[0]);

	Set(0, 1, inX[1]);
	Set(1, 1, inY[1]);
	Set(2, 1, inZ[1]);

	Set(0, 2, inX[2]);
	Set(1, 2, inY[2]);
	Set(2, 2, inZ[2]);
}

void Matrix3x3::SetScale(Vector3 inScale)
{
	Set(0, 0, inScale[0]);
	Set(0, 1, 0.0F);
	Set(0, 2, 0.0F);

	Set(1, 0, 0.0F);
	Set(1, 1, inScale[1]);
	Set(1, 2, 0.0F);

	Set(2, 0, 0.0F);
	Set(2, 1, 0.0F);
	Set(2, 2, inScale[2]);
}

bool Matrix3x3::IsIdentity(float threshold)
{
	if (Math::Approximately(Get(0, 0), 1.0f) &&
		Math::Approximately(Get(0, 1), 0.0f) &&
		Math::Approximately(Get(0, 2), 0.0f) &&
		Math::Approximately(Get(1, 0), 0.0f) &&
		Math::Approximately(Get(1, 1), 1.0f) &&
		Math::Approximately(Get(1, 2), 0.0f) &&
		Math::Approximately(Get(2, 0), 0.0f) &&
		Math::Approximately(Get(2, 1), 0.0f) &&
		Math::Approximately(Get(2, 2), 1.0f))
		return true;
	return false;
}
