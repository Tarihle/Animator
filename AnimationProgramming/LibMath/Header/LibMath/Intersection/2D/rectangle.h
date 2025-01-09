#ifndef __LIBMATH__INTERSECTION__2D__RECTANGLE_H__
#define __LIBMATH__INTERSECTION__2D__RECTANGLE_H__

#include <vector>

#include "LibMath/Intersection/Point.h"
#include "LibMath/Intersection/2D/Line.h"
#include "LibMath/Angle.h"

namespace LibMath
{
	class Rectangle {
	public:
		Rectangle(void) = delete;

		Rectangle(const Rectangle& other) = default;

		Rectangle(Rectangle&& other) = default;

		explicit Rectangle(const Point2D& center, float width, float height, Degree rotation = 0_deg);

		const Point2D& GetCenter(void) const;

		const Vec2 GetSize(void) const;

		const float& GetWidth(void) const;

		const float& GetHeight(void) const;

		const Degree& GetRotation(void) const;

		std::vector<Vertex2D> GetVertices(void) const;

		std::pair<Vertex2D, Vertex2D> GetMinMax(void) const;

		std::vector<Line> GetSides(void) const;

		void SetCenter(Point2D center);

		void SetSize(Vec2 size);

		void SetWidth(float width);

		void SetHeight(float height);

		void SetRotation(Degree rotation);

		Rectangle& operator=(const Rectangle& rhs) = default;

		Rectangle& operator=(Rectangle&& rhs) = default;

		~Rectangle(void) = default;

	private:
		Point2D m_Center;
		float m_Width, m_Height;
		Degree m_Rotation;
	};
}

#endif // !__LIBMATH__INTERSECTION__2D__RECTANGLE_H__
