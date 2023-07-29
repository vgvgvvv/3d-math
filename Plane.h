#pragma once
#include "Ray.h"
#include "Vector3.h"
#include "MathLibAPI.h"

class MATHLIB_API Plane
{

    Vector3 m_Normal;
    float m_Distance;
public:

    // Normal vector of the plane.
    Vector3 GetNormal() { return m_Normal; }
    void SetNormal(Vector3 value) { m_Normal = value; }

    // Distance from the origin to the plane.
    float GetDistance() { return m_Distance; }
    void SetDistance(float value) { m_Distance = value; }
	
    // Creates a plane.
    Plane(Vector3 inNormal, Vector3 inPoint)
    {
        m_Normal = Vector3::Normalize(inNormal);
        m_Distance = -Vector3::Dot(m_Normal, inPoint);
    }

    // Creates a plane.
    Plane(Vector3 inNormal, float d)
    {
        m_Normal = Vector3::Normalize(inNormal);
        m_Distance = d;
    }

    // Creates a plane.
    Plane(Vector3 a, Vector3 b, Vector3 c)
    {
        m_Normal = Vector3::Normalize(Vector3::Cross(b - a, c - a));
        m_Distance = -Vector3::Dot(m_Normal, a);
    }

    // Sets a plane using a point that lies within it plus a normal to orient it (note that the normal must be a normalized vector).
    void SetNormalAndPosition(Vector3 inNormal, Vector3 inPoint)
    {
        m_Normal = Vector3::Normalize(inNormal);
        m_Distance = -Vector3::Dot(inNormal, inPoint);
    }

    // Sets a plane using three points that lie within it.  The points go around clockwise as you look down on the top surface of the plane.
    void Set3Points(Vector3 a, Vector3 b, Vector3 c);

    // Make the plane face the opposite direction
    void Flip();

    // Return a version of the plane that faces the opposite direction
    Plane flipped() const;

        // Translates the plane into a given direction
    void Translate(Vector3 translation);

    // Creates a plane that's translated into a given direction
    static Plane Translate(Plane plane, Vector3 translation) { return {plane.m_Normal, plane.m_Distance += Vector3::Dot(plane.m_Normal, translation)
    }; }

    // Calculates the closest point on the plane.
    Vector3 ClosestPointOnPlane(Vector3 point) const;

    // Returns a signed distance from plane to point.
    float GetDistanceToPoint(Vector3 point) const;

    // Is a point on the positive side of the plane?
    bool GetSide(Vector3 point) const;

    // Are two points on the same side of the plane?
    bool SameSide(Vector3 inPt0, Vector3 inPt1) const;

    // Intersects a ray with the plane.
    bool Raycast(Ray ray, float& enter) const;

    // override string ToString()
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
    //         format = "F1";
    //     return String.Format("(normal:{0}, distance:{1})", m_Normal.ToString(format, formatProvider), m_Distance.ToString(format, formatProvider));
    // }
};
