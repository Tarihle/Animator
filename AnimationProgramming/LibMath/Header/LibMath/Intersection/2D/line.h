#ifndef __LIBMATH__INTERSECTION__2D__LINE_H__
#define __LIBMATH__INTERSECTION__2D__LINE_H__

#include "LibMath/Intersection/Point.h"

namespace LibMath
{
	class Line {
	public:
		Line(void) = delete;

		Line(const Line& other) = default;

		Line(Line&& other) = default;

		explicit Line(const Point2D& start, const Point2D& end);

		const Point2D&	GetStart(void) const;

		const Point2D&	GetEnd(void) const;		

		const float		GetSlope(void) const;
		
		void	SetStart(Point2D point);

		void	SetEnd(Point2D point);

		float	Length(void) const;

		float	LengthSquared(void) const;

		Line&	operator=(const Line& rhs) = default;

		Line&	operator=(Line&& rhs) = default;

		~Line(void) = default;

	private:
		Point2D m_Start;
		Point2D m_End;
	};
}

#endif // !__LIBMATH__INTERSECTION__2D__LINE_H__
