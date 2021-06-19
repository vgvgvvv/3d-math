//
// Created by 董宸 on 2021/6/19.
//

#pragma once

#include "Vector3.h"


class Ray {
private:
	Vector3 m_Origin;
    Vector3 m_Direction;

    // Creates a ray starting at /origin/ along /direction/.
public:
	Ray(Vector3 origin, Vector3 direction)
    {
        m_Origin = origin;
        m_Direction = direction.normalized();
    }

    Vector3 GetOrigin() const { return m_Origin; }

	void SetOrigin(Vector3 value) { m_Origin = value; }

    Vector3 GetDirection() const { return m_Direction; }

    void SetDirection(Vector3 value) { m_Direction = value.normalized(); }

    // Returns a point at /distance/ units along the ray.
	Vector3 GetPoint(float distance) const;

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
	//     return String.Format("Origin: {0}, Dir: {1}", m_Origin.ToString(format, formatProvider), m_Direction.ToString(format, formatProvider));
	// }
};


