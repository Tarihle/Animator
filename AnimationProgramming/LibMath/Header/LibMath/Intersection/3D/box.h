#ifndef __LIBMATH__INTERSECTION__3D__BOX_H__
#define __LIBMATH__INTERSECTION__3D__BOX_H__

#include <vector>

#include "LibMath/Intersection/Point.h"
#include "LibMath/Intersection/3D/Ray.h"
#include "LibMath/Matrix/Matrix.h"

#define AABB_NORMAL_AXIS 3

namespace LibMath
{
	class Box
	{
	public:

		Box() = default;

		explicit Box(const Point3D& center, const float width, 
					 const float height, const float depth, Mat4 rotation = LibMath::Mat4::Identity());

		Box(const Box& other) = default;

		Box(Box&& other) = default;

		const Point3D&	GetCenter(void) const;

		const Mat4&		GetRotation(void) const;

		const float&	GetWidth(void) const;

		const float&	GetHeight(void) const;

		const float&	GetDepth(void) const;

		//std::vector<Vertex2D> GetVertices(void) const;

		std::pair<Vertex3D, Vertex3D> GetMinMax(void) const;

		//std::vector<Line> GetSides(void) const;

		//std::vector<Line> GetPlanes(void) const;

		void	SetCenter(Point3D point);

		void	SetRotation(Mat4 matrix);

		void	SetWidth(float value);

		void	SetHeight(float value);

		void	SetDepth(float value);

		Box&	operator=(const Box& rhs) = default;

		Box&	operator=(Box&& rhs) = default;

		~Box() = default;
	private:
		Point3D m_Center = Vec3::zero();
		Mat4 m_Rotation = Mat4::Zero();
		float m_Width = 0.f;
		float m_Height = 0.f;
		float m_Depth = 0.f;
	};
}

#endif // !__LIBMATH__INTERSECTION__3D__BOX_H__
