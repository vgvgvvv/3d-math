//
// Created by 董宸 on 2021/6/19.
//

#pragma once
#include "Matrix3x3.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Utility.h"
#include "3d-math_API.h"

struct _3d_math_API FrustumPlanes
{
    float left;
    float right;
    float bottom;
    float top;
    float zNear;
    float zFar;
};

class _3d_math_API Matrix4x4 {
public:
    // memory layout:
        //
        //                row no (=vertical)
        //               |  0   1   2   3
        //            ---+----------------
        //            0  | m00 m10 m20 m30
        // column no  1  | m01 m11 m21 m31
        // (=horiz)   2  | m02 m12 m22 m32
        //            3  | m03 m13 m23 m33

        ///*undocumented*
    float m00;
    ///*undocumented*
    float m10;
    ///*undocumented*
    float m20;
    ///*undocumented*
    float m30;

    ///*undocumented*
    float m01;
    ///*undocumented*
    float m11;
    ///*undocumented*
    float m21;
    ///*undocumented*
    float m31;

    ///*undocumented*
    float m02;
    ///*undocumented*
    float m12;
    ///*undocumented*
    float m22;
    ///*undocumented*
    float m32;

    ///*undocumented*
    float m03;
    ///*undocumented*
    float m13;
    ///*undocumented*
    float m23;
    ///*undocumented*
    float m33;

    // Matrix4x4.zero is of questionable usefulness considering C# sets everything to 0 by default, however:
    //  1. it's consistent with other Math structs in Unity such as Vector2, Vector3 and Vector4,
    //  2. "Matrix4x4.zero" is arguably more readable than "new Matrix4x4()",
    //  3. it's already in the API ..
    static const Matrix4x4 zeroMatrix;

    static const Matrix4x4 identityMatrix;

    Matrix4x4();
	
    Matrix4x4(Vector4 column0, Vector4 column1, Vector4 column2, Vector4 column3);

    Matrix4x4(
	    float m00, float m01, float m02, float m03,
	    float m10, float m11, float m12, float m13,
	    float m20, float m21, float m22, float m23,
	    float m30, float m31, float m32, float m33);

    // Access element at [row, column].
    float Get(int row, int column) const;

    void Set(int row, int column, float value);

    void Set(Matrix4x4 mat);

    // Access element at sequential index (0..15 inclusive).
    float Get(int index) const;

    void Set(int index, float value);

    float& operator[](int index);

    const float* ToArray() const;

    // // used to allow Matrix4x4s to be used as keys in hash tables
    //     override int GetHashCode()
    // {
    //     return GetColumn(0).GetHashCode() ^ (GetColumn(1).GetHashCode() << 2) ^ (GetColumn(2).GetHashCode() >> 2) ^ (GetColumn(3).GetHashCode() >> 1);
    // }
    //
    // // also required for being able to use Matrix4x4s as keys in hash tables
    // override bool Equals(object other)
    // {
    //     if (!(other is Matrix4x4)) return false;
    //
    //     return Equals((Matrix4x4)other);
    // }
    //
    // bool Equals(Matrix4x4 other)
    // {
    //     return GetColumn(0).Equals(other.GetColumn(0))
    //         && GetColumn(1).Equals(other.GetColumn(1))
    //         && GetColumn(2).Equals(other.GetColumn(2))
    //         && GetColumn(3).Equals(other.GetColumn(3));
    // }

    // Multiplies two matrices.
    Matrix4x4 operator*(Matrix4x4 rhs) const;

    // Transforms a [[Vector4]] by a matrix.
    Vector4 operator*(Vector4 vector) const;

    //*undoc*
    bool operator==(Matrix4x4 rhs) const;

    //*undoc*
    bool operator!=(Matrix4x4 rhs) const;

    // Get a column of the matrix.
    Vector4 GetColumn(int index) const;

    // Returns a row of the matrix.
    Vector4 GetRow(int index);

    // Sets a column of the matrix.
    void SetColumn(int index, Vector4 column);

    // Sets a row of the matrix.
    void SetRow(int index, Vector4 row);

    // Transforms a position by this matrix, with a perspective divide. (generic)
    Vector3 MultiplyPoint(Vector3 point) const;

    // Transforms a position by this matrix, without a perspective divide. (fast)
    Vector3 MultiplyPoint3x4(Vector3 point) const;

    // Transforms a direction by this matrix.
    Vector3 MultiplyVector(Vector3 vector) const;

    // Transforms a plane by this matrix.
    Plane TransformPlane(Plane plane);

    // Creates a scaling matrix.
    static Matrix4x4 Scale(Vector3 vector);

    // Creates a translation matrix.
    static Matrix4x4 Translate(Vector3 vector);

    // Creates a rotation matrix. Note: Assumes unit quaternion
    static Matrix4x4 Rotate(Quaternion q);


    //     override string ToString()
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
    //         format = "F5";
    //     return String.Format("{0}\t{1}\t{2}\t{3}\n{4}\t{5}\t{6}\t{7}\n{8}\t{9}\t{10}\t{11}\n{12}\t{13}\t{14}\t{15}\n",
    //         m00.ToString(format, formatProvider), m01.ToString(format, formatProvider), m02.ToString(format, formatProvider), m03.ToString(format, formatProvider),
    //         m10.ToString(format, formatProvider), m11.ToString(format, formatProvider), m12.ToString(format, formatProvider), m13.ToString(format, formatProvider),
    //         m20.ToString(format, formatProvider), m21.ToString(format, formatProvider), m22.ToString(format, formatProvider), m23.ToString(format, formatProvider),
    //         m30.ToString(format, formatProvider), m31.ToString(format, formatProvider), m32.ToString(format, formatProvider), m33.ToString(format, formatProvider));
    // }

    bool IsIdentity() const;

    float GetDeterminant() const;


    bool isIdentity(){ return IsIdentity(); }
    float determinant() { return GetDeterminant(); }

    static float Determinant(Matrix4x4 m) { return m.determinant(); }

    static Matrix4x4 TRS(Vector3 pos, Quaternion q, Vector3 s);

    void SetTRS(Vector3 pos, Quaternion q, Vector3 s);

    static Matrix4x4 Inverse(Matrix4x4 m);
    Matrix4x4 inverse(){ return Matrix4x4::Inverse(*this); }

    static Matrix4x4 Transpose(Matrix4x4 m);

    Matrix4x4 transpose() const;

    static Matrix4x4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

    static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);

    static Matrix4x4 Frustum(float left, float right, float bottom, float top, float nearval, float farval);

    static Matrix4x4 Frustum1(const FrustumPlanes& fp);


};


