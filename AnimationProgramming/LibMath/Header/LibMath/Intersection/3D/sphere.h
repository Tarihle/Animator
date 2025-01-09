#ifndef __LIBMATH__INTERSECTION__3D__SPHERE_H__
#define __LIBMATH__INTERSECTION__3D__SPHERE_H__

#include "LibMath/Intersection/point.h"

namespace LibMath
{
	class Sphere
	{
	public:

		Sphere(void) = delete;

		Sphere(const Sphere&) = default;

		Sphere(Sphere&&) = default;

		explicit Sphere(const Point3D& center, const float radius = 1.f);

		const Point3D&	GetCenter() const;

		const float&	GetRadius() const;

		void	SetCenter(Point3D point);

		void	SetRadius(float radius);

		Sphere& operator=(const Sphere&) = default;

		Sphere& operator=(Sphere&& rhs) = default;

		~Sphere() = default;

	private:
		Point3D m_Center = Vec3::zero();
		float m_Radius = 0.f;
	};
}

#endif // !__LIBMATH__INTERSECTION__3D__SPHERE_H__
