#ifndef __LIBMATH__INTERSECTION__3D_COLLISION_H__
#define __LIBMATH__INTERSECTION__3D_COLLISION_H__

#include <vector>

#include "LibMath/Intersection/3D/Sphere.h"
#include "LibMath/Intersection/3D/Box.h"
#include "LibMath/Intersection/3D/Plane.h"

namespace LibMath
{
	bool RayToSphere(const Ray& ray, const Sphere& sph);

	std::pair<LibMath::Vec3, bool> RayToAABB(const Ray& ray, float raySize, const Box& aabb);

	bool SpheretoSphere(const Sphere& alpha, const Sphere& beta);

	std::pair<float, bool> SphereToAABB(const Sphere& sph, const Box& aabb);

	bool PointToSphere(const Point3D& dot, const Sphere& sph);

	bool PointToAABB(const Point3D& dot, const Box& box);

	bool AABBToAABB(const Box& alpha, const Box& beta);
}

#endif // !__LIBMATH__INTERSECTION__3D_COLLISION_H__
