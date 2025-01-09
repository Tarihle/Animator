#include "LibMath/Intersection/3D/Ray.h"

namespace LibMath
{
	Ray::Ray(const Point3D& origin, const Vec3& direction) : m_Origin(origin), m_Direction(direction) {}
	
	const Point3D& Ray::GetOrigin() const
	{
		return m_Origin;
	}
	
	const Vec3& Ray::GetDirection() const
	{
		return m_Direction;
	}
	
	void Ray::SetOrigin(Point3D point)
	{
		m_Origin = point;
	}
	
	void Ray::SetDirection(Vec3 dir)
	{
		m_Direction = dir;
	}
}
