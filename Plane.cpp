#include "Plane.h"

#include "Utility.h"

void Plane::Set3Points(Vector3 a, Vector3 b, Vector3 c)
{
	m_Normal = Vector3::Normalize(Vector3::Cross(b - a, c - a));
	m_Distance = -Vector3::Dot(m_Normal, a);
}

void Plane::Flip()
{
	m_Normal = -m_Normal;
	m_Distance = -m_Distance;
}

Plane Plane::flipped() const
{
	return {-m_Normal, -m_Distance};
}

void Plane::Translate(Vector3 translation)
{
	m_Distance += Vector3::Dot(m_Normal, translation);
}

Vector3 Plane::ClosestPointOnPlane(Vector3 point) const
{
	auto pointToPlaneDistance = Vector3::Dot(m_Normal, point) + m_Distance;
	return point - (m_Normal * pointToPlaneDistance);
}

float Plane::GetDistanceToPoint(Vector3 point) const
{
	return Vector3::Dot(m_Normal, point) + m_Distance;
}

bool Plane::GetSide(Vector3 point) const
{
	return Vector3::Dot(m_Normal, point) + m_Distance > 0.0F;
}

bool Plane::SameSide(Vector3 inPt0, Vector3 inPt1) const
{
	float d0 = GetDistanceToPoint(inPt0);
	float d1 = GetDistanceToPoint(inPt1);
	return (d0 > 0.0f && d1 > 0.0f) ||
		(d0 <= 0.0f && d1 <= 0.0f);
}

bool Plane::Raycast(Ray ray, float& enter) const
{
	float vdot = Vector3::Dot(ray.GetDirection(), m_Normal);
	float ndot = -Vector3::Dot(ray.GetOrigin(), m_Normal) - m_Distance;

	if (Math::Approximately(vdot, 0.0f))
	{
		enter = 0.0F;
		return false;
	}

	enter = ndot / vdot;

	return enter > 0.0F;
}
