#include "LibMath/Arithmetic.h"

#include "LibMath/Intersection/2D/Line.h"

namespace LibMath
{
	Line::Line(const Point2D& start, const Point2D& end) : m_Start(start), m_End(end) {}
	
	const Point2D& Line::GetStart(void) const
	{
		return m_Start;
	}
	
	const Point2D& Line::GetEnd(void) const
	{
		return m_End;
	}

	const float Line::GetSlope(void) const
	{
		return (m_End.m_y - m_Start.m_y) / (m_End.m_x - m_Start.m_x);
	}
	
	void Line::SetStart(Point2D point)
	{
		m_Start = point;
	}
	
	void Line::SetEnd(Point2D point)
	{
		m_End = point;
	}
	
	float Line::Length(void) const
	{
		float x = (m_End.m_x - m_Start.m_x);
		float y = (m_End.m_y - m_Start.m_y);
		
		return SquareRoot(x * x + y * y);
	}
	
	float Line::LengthSquared(void) const
	{
		float x = (m_End.m_x - m_Start.m_x);
		float y = (m_End.m_y - m_Start.m_y);

		return (x * x + y * y);
	}
}
