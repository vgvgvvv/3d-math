//
// Created by 董宸 on 2021/6/19.
//
#pragma once

#include "3d-math_API.h"

class Vector3;

class _3d_math_API Matrix3x3 {
public:
    ///*undocumented*
    float m00;
    ///*undocumented*
    float m10;
    ///*undocumented*
    float m20;

    ///*undocumented*
    float m01;
    ///*undocumented*
    float m11;
    ///*undocumented*
    float m21;

    ///*undocumented*
    float m02;
    ///*undocumented*
    float m12;
    ///*undocumented*
    float m22;

    // Returns a matrix with all elements set to zero (RO).
    static const Matrix3x3 zero;

    static const Matrix3x3 IdentityMatrix;
	
    Matrix3x3();

    Matrix3x3(Vector3 column0, Vector3 column1, Vector3 column2);

    Matrix3x3(
	    float m00, float m01, float m02,
	    float m10, float m11, float m12,
	    float m20, float m21, float m22);

    // Access element at [row, column].
    float Get(int row, int column);

    void Set(int row, int column, float value);

    float Get(int index) const;

    void Set(int index, float value);

    float& operator[](int index);

    const float* ToArray() const;

    // override int GetHashCode()
    // {
    //     return GetColumn(0).GetHashCode() ^ (GetColumn(1).GetHashCode() << 2) ^ (GetColumn(2).GetHashCode() >> 2) ^ (GetColumn(3).GetHashCode() >> 1);
    // }
    //
    // // also required for being able to use Matrix4x4s as keys in hash tables
    // override bool Equals(object other)
    // {
    //     if (!(other is Matrix3x3)) return false;
    //
    //     return Equals((Matrix3x3)other);
    // }
    //
    // bool Equals(Matrix3x3 other)
    // {
    //     return GetColumn(0).Equals(other.GetColumn(0))
    //         && GetColumn(1).Equals(other.GetColumn(1))
    //         && GetColumn(2).Equals(other.GetColumn(2))
    //         && GetColumn(3).Equals(other.GetColumn(3));
    // }

    // Multiplies two matrices.
    Matrix3x3 operator*(Matrix3x3 rhs) const;

    // Transforms a [[Vector4]] by a matrix.
    class Vector4 operator*(Vector3 vector) const;

    //*undoc*
    bool operator==(Matrix3x3 rhs) const;

    //*undoc*
    bool operator!=(Matrix3x3 rhs) const;

    // Get a column of the matrix.
    Vector3 GetColumn(int index) const;

    // Returns a row of the matrix.
    Vector3 GetRow(int index) const;

    // Sets a column of the matrix.
    void SetColumn(int index, Vector3 column);

    // Sets a row of the matrix.
    void SetRow(int index, Vector3 row);

    Vector3 MultiplyVector(Vector3 vector) const;

    static Matrix3x3 FromEuler(Vector3 v);

    bool ToEuler(Vector3& v);


    static Matrix3x3 FromToRotation(Vector3 from, Vector3 to);

    static bool LookRotationToMatrix(Vector3 viewVec, Vector3 upVec, Matrix3x3& m);


private:
    void SanitizeEuler(Vector3& euler);

    static void MakePositive(Vector3& euler);

    void SetIdentity();

    void SetZero();

    void SetOrthoNormalBasis(Vector3 inX, Vector3 inY, Vector3 inZ);

    void SetOrthoNormalBasisInverse(Vector3 inX, Vector3 inY, Vector3 inZ);

    void SetScale(Vector3 inScale);

    bool IsIdentity(float threshold);
	
    //     override string ToString()
    // {
    //     return ToString(null, CultureInfo.InvariantCulture.NumberFormat);
    // }
    //
    // string ToString(string format)
    // {
    //     return ToString(format, CultureInfo.InvariantCulture.NumberFormat);
    // }
    //
    // string ToString(string format, IFormatProvider formatProvider)
    // {
    //     if (string.IsNullOrEmpty(format))
    //         format = "F5";
    //     return String.Format(
    //         "{0}\t{1}\t{2}\n{3}\t{4}\t{5}\n{6}\t{7}\t{8}",
    //         m00.ToString(format, formatProvider),
    //         m01.ToString(format, formatProvider),
    //         m02.ToString(format, formatProvider),
    //
    //         m10.ToString(format, formatProvider),
    //         m11.ToString(format, formatProvider),
    //         m12.ToString(format, formatProvider),
    //
    //         m20.ToString(format, formatProvider),
    //         m21.ToString(format, formatProvider),
    //         m22.ToString(format, formatProvider));
    // }
};


