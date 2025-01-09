#ifndef __LIBMATH__INTERSECTION__2D__CIRCLE_H__
#define __LIBMATH__INTERSECTION__2D__CIRCLE_H__

#include "LibMath/Intersection/Point.h"

namespace LibMath
{
	class Circle {
	public:
		Circle(void) = delete;

		Circle(const Circle& other) = default;

		Circle(Circle&& other) = default;

		explicit Circle(const Point2D& center, float radius = 1.f);

		const Point2D&	GetCenter(void) const;

		const float&	GetRadius(void) const;

		void	SetCenter(Point2D point);
		
		void	SetRadius(float radius);

		Circle&	operator=(const Circle& rhs) = default;

		Circle&	operator=(Circle&& rhs) = default;

		~Circle(void) = default;

	private:
		Point2D m_Center;
		float m_Radius;
	};
}

#endif // !__LIBMATH__INTERSECTION__2D__CIRCLE_H__
