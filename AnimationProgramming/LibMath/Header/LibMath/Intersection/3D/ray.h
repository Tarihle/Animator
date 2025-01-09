#ifndef __LIBMATH__INTERSECTION__3D__RAY_H__
#define __LIBMATH__INTERSECTION__3D__RAY_H__

#include "LibMath/Intersection/Point.h"

namespace LibMath
{
	class Ray
	{
	public:

		Ray(void) = delete;

		Ray(const Ray&) = default;

		Ray(Ray&&) = default;

		explicit Ray(const Point3D& origin, const Vec3& direction);

		const Point3D&	GetOrigin() const;

		const Vec3&		GetDirection() const;

		void	SetOrigin(Point3D point);

		void	SetDirection(Vec3 dir);

		Ray&	operator=(const Ray& rhs) = default;
		
		Ray&	operator=(Ray&& rhs) = default;

		~Ray() = default;

	private:
		Point3D m_Origin;
		Vec3 m_Direction;
	};
}

#endif // !__LIBMATH__INTERSECTION__3D__RAY_H__
