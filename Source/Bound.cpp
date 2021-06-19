//
// Created by 董宸 on 2021/6/19.
//

#include "Bound.h"

bool Bounds::operator==(Bounds rhs) const
{
	// Returns false in the presence of NaN values.
	return (GetCenter() == rhs.GetCenter() && GetExtents() == rhs.GetExtents());
}

bool Bounds::operator!=(Bounds rhs) const
{
	// Returns true in the presence of NaN values.
	return !(*this == rhs);
}

void Bounds::SetMinMax(Vector3 min, Vector3 max)
{
	SetExtents((max - min) * 0.5F);
	SetCenter(GetMin() + GetExtents());
}

void Bounds::Encapsulate(Bounds bounds)
{
	Encapsulate(bounds.GetCenter() - bounds.GetExtents());
	Encapsulate(bounds.GetCenter() + bounds.GetExtents());
}

void Bounds::Expand(float amount)
{
	amount *= .5f;
	m_Extents = m_Extents + Vector3(amount, amount, amount);
}

void Bounds::Expand(Vector3 amount)
{
	m_Extents = m_Extents + amount * .5f;
}

bool Bounds::Intersects(Bounds bounds)
{
	auto min = GetMin();
	auto max = GetMax();
	auto otherMin = bounds.GetMin();
	auto otherMax = bounds.GetMax();
	return (min.x <= otherMax.x) && (max.x >= otherMin.x) &&
		(min.y <= otherMax.y) && (max.y >= otherMin.y) &&
		(min.z <= otherMax.z) && (max.z >= otherMin.z);
}

bool Bounds::IntersectRay(Ray ray) const
{
	float dist1;
	float dist2;
	return IntersectRayAABB(ray, *this, dist1, dist2);
}

bool Bounds::IntersectRay(Ray ray, float& distance1, float& distance2) const
{
	return IntersectRayAABB(ray, *this, distance1, distance2);
}

bool Bounds::Contains(Vector3 point) const
{
	auto min = GetMin();
	auto max = GetMax();
	return min.x <= point.x && max.x > point.x &&
		min.y <= point.y && max.y > point.y &&
		min.z <= point.z && max.z > point.z;
}

float Bounds::SqrDistance(Vector3 point) const
{
	Vector3 closest = point - GetCenter();
	float sqrDistance = 0.0f;

	for (int i = 0; i < 3; ++i)
	{
		float clos = closest[i];
		float ext = GetExtents()[i];
		if (clos < -ext)
		{
			float delta = clos + ext;
			sqrDistance += delta * delta;
			closest[i] = -ext;
		}
		else if (clos > ext)
		{
			float delta = clos - ext;
			sqrDistance += delta * delta;
			closest[i] = ext;
		}
	}

	return sqrDistance;
}

Vector3 Bounds::ClosestPoint(Vector3 point, float& distance) const
{
	// compute coordinates of point in box coordinate system
	Vector3 closest = point - GetCenter();
	Vector3 outPoint;

	// project test point onto box
	float fSqrDistance = 0.0f;
	float fDelta;

	for (int i = 0; i < 3; i++)
	{
		if (closest[i] < -GetExtents()[i])
		{
			fDelta = closest[i] + GetExtents()[i];
			fSqrDistance += fDelta * fDelta;
			closest[i] = -GetExtents()[i];
		}
		else if (closest[i] > GetExtents()[i])
		{
			fDelta = closest[i] - GetExtents()[i];
			fSqrDistance += fDelta * fDelta;
			closest[i] = GetExtents()[i];
		}
	}

	// Inside
	if (fSqrDistance == 0.0F)
	{
		outPoint = point;
		distance = 0.0F;
	}
		// Outside
	else
	{
		outPoint = closest + GetCenter();
		distance = fSqrDistance;
	}

	return outPoint;
}

bool Bounds::IntersectRayAABB(Ray ray, Bounds bounds, float& dist1, float& dist2)
{
	dist1 = dist2 = Math::Infinity;
	float tmin = -Math::Infinity;
	float tmax = Math::Infinity;

	float t0, t1, f;

	Vector3 p = bounds.GetCenter() - ray.GetOrigin();
	Vector3 extent = bounds.GetExtents();
	int i;
	for (i = 0; i < 3; i++)
	{
		// ray and plane are paralell so no valid intersection can be found
		{
			f = 1.0F / ray.GetDirection()[i];
			t0 = (p[i] + extent[i]) * f;
			t1 = (p[i] - extent[i]) * f;
			// Ray leaves on Right, Top, Back Side
			if (t0 < t1)
			{
				if (t0 > tmin)
					tmin = t0;

				if (t1 < tmax)
					tmax = t1;

				if (tmin > tmax)
					return false;

				if (tmax < 0.0F)
					return false;
			}
			// Ray leaves on Left, Bottom, Front Side
			else
			{
				if (t1 > tmin)
					tmin = t1;

				if (t0 < tmax)
					tmax = t0;

				if (tmin > tmax)
					return false;

				if (tmax < 0.0F)
					return false;
			}
		}
	}

	dist1 = tmin;
	dist2 = tmax;

	return true;
}
