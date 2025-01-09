#include "LibMath/Intersection/3D/sphere.h"

namespace LibMath
{
	Sphere::Sphere(const Point3D& center, const float radius) : m_Center(center), m_Radius(radius) {}
	
	const Point3D& Sphere::GetCenter() const
	{
		return m_Center;
	}
	
	const float& Sphere::GetRadius() const
	{
		return m_Radius;
	}
	
	void Sphere::SetCenter(Point3D point)
	{
		m_Center = point;
	}
	
	void Sphere::SetRadius(float radius)
	{
		m_Radius = radius;
	}
}
