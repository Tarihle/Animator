#include "LibMath/Intersection/2D/Rectangle.h"

#include "LibMath/Trigonometry.h"

namespace LibMath
{
	Rectangle::Rectangle(const Point2D& center, float width, float height, Degree rotation) :
		m_Center(center), m_Width(width), m_Height(height), m_Rotation(rotation) {}
	
	const Point2D& Rectangle::GetCenter(void) const
	{
		return m_Center;
	}
	
	const Vec2 Rectangle::GetSize(void) const
	{
		return Vec2(m_Width, m_Height);
	}
	
	const float& Rectangle::GetWidth(void) const
	{
		return m_Width;
	}
	
	const float& Rectangle::GetHeight(void) const
	{
		return m_Height;
	}

	const Degree& Rectangle::GetRotation(void) const
	{
		return m_Rotation;
	}

	std::vector<Vertex2D> Rectangle::GetVertices(void) const
	{
		std::vector<Vertex2D> vertices;

		Radian rotation1 = (m_Rotation + 135_deg);
		Radian rotation2 = (m_Rotation + 45_deg);

		Vertex2D firstVertex
		{
			m_Center.m_x + LibMath::cos(rotation1) * m_Width,
			m_Center.m_y + LibMath::sin(rotation1) * m_Height
		};
		
		Vertex2D secondVertex
		{
			m_Center.m_x + LibMath::cos(rotation2) * m_Width,
			m_Center.m_y + LibMath::sin(rotation2) * m_Height
		};

		Vertex2D thirdVertex
		{
			m_Center.m_x - LibMath::cos(rotation1) * m_Width,
			m_Center.m_y - LibMath::sin(rotation1) * m_Height
		};

		Vertex2D fourthVertex
		{
			m_Center.m_x - LibMath::cos(rotation2) * m_Width,
			m_Center.m_y - LibMath::sin(rotation2) * m_Height
		};

		vertices.push_back(firstVertex);
		vertices.push_back(secondVertex);
		vertices.push_back(thirdVertex);
		vertices.push_back(fourthVertex);

		return vertices;
	}

	std::pair<Vertex2D, Vertex2D> Rectangle::GetMinMax(void) const
	{
		std::vector<Vertex2D> vertices = this->GetVertices();

		Vertex2D min = vertices[0];
		Vertex2D max = vertices[0];

		for (int i = 1; i < 4; i++)
		{
			if (vertices[i].m_x < min.m_x)
				min.m_x = vertices[i].m_x;
			if (vertices[i].m_y < min.m_y)
				min.m_y = vertices[i].m_y;

			if (vertices[i].m_x > max.m_x)
				max.m_x = vertices[i].m_x;
			if (vertices[i].m_y > max.m_y)
				max.m_y = vertices[i].m_y;
		}

		return std::make_pair(min, max);
	}

	std::vector<Line> Rectangle::GetSides(void) const
	{
		std::vector<Line> sides;
		std::vector<Vertex2D> vertices = this->GetVertices();

		for (int i = 0; i < 3; i++)
		{
			sides.emplace_back(vertices[i], vertices[i + 1]);
		}

		sides.emplace_back(vertices[3], vertices[0]);

		return sides;
	}
	
	void Rectangle::SetCenter(Point2D center)
	{
		m_Center = center;
	}
	
	void Rectangle::SetSize(Vec2 size)
	{
		m_Width = size.m_x;
		m_Height = size.m_y;
	}
	
	void Rectangle::SetWidth(float width)
	{
		m_Width = width;
	}
	
	void Rectangle::SetHeight(float height)
	{
		m_Height = height;
	}

	void Rectangle::SetRotation(Degree rotation)
	{
		m_Rotation = rotation;
	}
}
