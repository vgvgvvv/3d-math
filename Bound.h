//
// Created by 董宸 on 2021/6/19.
//

#pragma once
#include "Ray.h"
#include "Vector3.h"
#include "3d-math_API.h"

class _3d_math_API Bounds {
    Vector3 m_Center;
    Vector3 m_Extents;

public:
    // Creates new Bounds with a given /center/ and total /size/. Bound ::ref::extents will be half the given size.
    Bounds(Vector3 center, Vector3 size)
    {
        m_Center = center;
        m_Extents = size * 0.5F;
    }

    // // used to allow Bounds to be used as keys in hash tables
    // override int GetHashCode()
    // {
    //     return center.GetHashCode() ^ (extents.GetHashCode() << 2);
    // }
    //
    // // also required for being able to use Vector4s as keys in hash tables
    // override bool Equals(object other)
    // {
    //     if (!(other is Bounds)) return false;
    //
    //     return Equals((Bounds)other);
    // }
    //
    // bool Equals(Bounds other)
    // {
    //     return center.Equals(other.center) && extents.Equals(other.extents);
    // }

    // The center of the bounding box.
    Vector3 GetCenter() const { return m_Center; }
    void SetCenter(Vector3 value) { m_Center = value; }

    // The total size of the box. This is always twice as large as the ::ref::extents.
    Vector3 GetSize() const { return m_Extents * 2.0f; }
    void SetSize(Vector3 value) { m_Extents = value * 0.5f; }

    // The extents of the box. This is always half of the ::ref::size.
    Vector3 GetExtents() const { return m_Extents; }
    void SetExtents(Vector3 value) { m_Extents = value; }

    // The minimal point of the box. This is always equal to ''center-extents''.
    Vector3 GetMin() const { return GetCenter() - GetExtents(); }
    void SetMin(Vector3 value) { SetMinMax(value, GetMax()); }

    // The maximal point of the box. This is always equal to ''center+extents''.
    Vector3 GetMax() const { return GetCenter() + GetExtents(); }
    void SetMax(Vector3 value) { SetMinMax(GetMin(), value); }


    //*undoc*
    bool operator==(Bounds rhs) const;

    //*undoc*
    bool operator!=(Bounds rhs) const;

    // Sets the bounds to the /min/ and /max/ value of the box.
    void SetMinMax(Vector3 min, Vector3 max);

    // Grows the Bounds to include the /point/.
    void Encapsulate(Vector3 point)
    {
        SetMinMax(Vector3::Min(GetMin(), point), Vector3::Max(GetMax(), point));
    }

    // Grows the Bounds to include the /Bounds/.
    void Encapsulate(Bounds bounds);

    // Expand the bounds by increasing its /size/ by /amount/ along each side.
    void Expand(float amount);

    // Expand the bounds by increasing its /size/ by /amount/ along each side.
    void Expand(Vector3 amount);

    // Does another bounding box intersect with this bounding box?
    bool Intersects(Bounds bounds);

    bool IntersectRay(Ray ray) const;

    bool IntersectRay(Ray ray, float& distance1, float& distance2) const;


    // /// *listonly*
    // override string ToString()
    // {
    //     return String.Format("Center: {0}, Extents: {1}", m_Center, m_Extents);
    // }
    //
    // // Returns a nicely formatted string for the bounds.
    // string ToString(string format)
    // {
    //     return String.Format("Center: {0}, Extents: {1}", m_Center.ToString(format), m_Extents.ToString(format));
    // }

    bool Contains(Vector3 point) const;

    float SqrDistance(Vector3 point) const;

    Vector3 ClosestPoint(Vector3 point, float& distance) const;

private:
    static bool IntersectRayAABB(Ray ray, Bounds bounds, float& dist1, float& dist2);
};
