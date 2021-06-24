//
// Created by 董宸 on 2021/6/19.
//

#include "Ray.h"

Vector3 Ray::GetPoint(float distance) const
{
	return m_Origin + m_Direction * distance;
}
