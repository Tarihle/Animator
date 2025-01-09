#include "LibMath/Intersection/2D/Circle.h"

namespace LibMath
{
	Circle::Circle(const Point2D& center, float radius) : m_Center(center), m_Radius(radius) {}
	
	const Point2D& Circle::GetCenter(void) const
	{
		return m_Center;
	}

	const float& Circle::GetRadius(void) const
	{
		return m_Radius;
	}

	void Circle::SetCenter(Point2D point)
	{
		m_Center = point;
	}
	
	void Circle::SetRadius(float radius)
	{
		m_Radius = radius;
	}
}