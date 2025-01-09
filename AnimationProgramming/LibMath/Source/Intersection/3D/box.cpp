#include "LibMath/Intersection/3D/Box.h"

namespace LibMath
{
	Box::Box(const Point3D& center, const float width, const float height, const float depth, Mat4 rotation)
	: m_Center(center), m_Width(width), m_Height(height), m_Depth(depth), m_Rotation(rotation) {}

	std::pair<Vertex3D, Vertex3D> Box::GetMinMax(void) const
	{
		Vertex3D min = m_Center;
		Vertex3D max = m_Center;

		min.m_x -= m_Width * 0.5f;
		min.m_y -= m_Height * 0.5f;
		min.m_z -= m_Depth * 0.5f;

		max.m_x += m_Width * 0.5f;
		max.m_y += m_Height * 0.5f;
		max.m_z += m_Depth * 0.5f;

		min = Vec4(min) * m_Rotation;
		max = Vec4(max) * m_Rotation;

		return std::make_pair(min, max);
	}

	const Point3D& Box::GetCenter() const
	{
		return m_Center;
	}

	const Mat4& Box::GetRotation() const
	{
		return m_Rotation;
	}

	const float& Box::GetWidth() const
	{
		return m_Width;
	}

	const float& Box::GetHeight() const
	{
		return m_Height;
	}

	const float& Box::GetDepth() const
	{
		return m_Depth;
	}

	void Box::SetCenter(Point3D point) 
	{
		m_Center = point;
	}

	void Box::SetRotation(Mat4 matrix)
	{
		m_Rotation = matrix;
	}

	void Box::SetWidth(float value)
	{
		m_Width = value;
	}

	void Box::SetHeight(float value)
	{
		m_Height = value;
	}

	void Box::SetDepth(float value)
	{
		m_Depth = value;
	}
}
