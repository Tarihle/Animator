#include "LiBMath/Intersection/3D/Collision3D.h"

namespace LibMath
{
	bool RayToSphere(const Ray& ray, const Sphere& sph)
	{
		Vec3 proj = sph.GetCenter();

		Vec3 dif = sph.GetCenter() - ray.GetOrigin();

		if (ray.GetDirection().dot(dif) <= 0)
			return false;

		proj.projectOnto(ray.GetDirection());

		return proj.distanceSquaredFrom(sph.GetCenter()) < (sph.GetRadius() * sph.GetRadius());
	}

	std::pair<Vec3, bool> RayToAABB(const Ray& ray, float raySize, const Box& aabb)
    {
        std::pair<Vertex3D, Vertex3D> minMax = aabb.GetMinMax();    /* Gets minimum and maximum vertices of the box */
        Vec3 origin = ray.GetOrigin();
        
        /* transforms normalized vector so it has a distance */
        Vec3 v = (ray.GetDirection()) * raySize;
        /* and adds it to its starting position */
        Vec3 newRay = origin + v;

        for (int i = 0; i < AABB_NORMAL_AXIS; i++)  /* repeat for each normal of the the box */
        {
            int j = (i + 1) % AABB_NORMAL_AXIS;    /* because we need to stay in range [0, 3[ */
            int k = (i + 2) % AABB_NORMAL_AXIS;    /* because we need to stay in range[0, 3[ */

            /* Checks if both ends of the newRay are on different sides of the plane */
            if (std::signbit(origin[i] - minMax.first[i]) != std::signbit(newRay[i] - minMax.first[i]))
            {
                /* apply equation of intersection between a vector and a plane */
                float t = (minMax.first[i] - origin[i]) / v[i];

                Vec3 newPoint = origin + v * t;
                if ((newPoint[j] >= minMax.first[j] && (newPoint[j] <= minMax.second[j])) &&
                    (newPoint[k] >= minMax.first[k] && (newPoint[k] <= minMax.second[k])))
                {
                    return std::make_pair(newPoint, true);
                }
            }
            /* Repeat for the opposite face */
            if (std::signbit(origin[i] - minMax.second[i]) != std::signbit(newRay[i] - minMax.second[i]))
            {
                float t = (minMax.second[i] - origin[i]) / v[i];

                Vec3 newPoint = origin + v * t;
                if ((newPoint[j] >= minMax.first[j] && (newPoint[j] <= minMax.second[j])) &&
                    (newPoint[k] >= minMax.first[k] && (newPoint[k] <= minMax.second[k])))
                {
                    return std::make_pair(newPoint, true);
                }
            }
        }

        return std::make_pair(Vec3(std::numeric_limits<float>::infinity()), false);
    }

	bool SpheretoSphere(const Sphere& alpha, const Sphere& beta)
	{
		float distanceSquared = (alpha.GetCenter().m_x - beta.GetCenter().m_x) * (alpha.GetCenter().m_x - beta.GetCenter().m_x) +
			(alpha.GetCenter().m_y - beta.GetCenter().m_y) * (alpha.GetCenter().m_y - beta.GetCenter().m_y) +
			(alpha.GetCenter().m_z - beta.GetCenter().m_z) * (alpha.GetCenter().m_z - beta.GetCenter().m_z);

		return distanceSquared < ((alpha.GetRadius() + beta.GetRadius()) * (alpha.GetRadius() + beta.GetRadius()));
	}

    std::pair<float, bool> SphereToAABB(const Sphere& sph, const Box& aabb)
    {
        float squaredDistance = 0.0f;
        bool collision = false;

        std::pair<Vertex3D, Vertex3D> minMax = aabb.GetMinMax();    /* Gets minimum and maximum vertices of the box */
        Vec3 sphereCenter = sph.GetCenter();

        for (int axis = 0; axis < AABB_NORMAL_AXIS; axis++)
        {
            /* If the center is between the min and max, then the distance is 0 */
            if (sphereCenter[axis] < minMax.first[axis])
                squaredDistance += (minMax.first[axis] - sphereCenter[axis]) * (minMax.first[axis] - sphereCenter[axis]);
            else if (sphereCenter[axis] > minMax.second[axis])
                squaredDistance += (sphereCenter[axis] - minMax.second[axis]) * (sphereCenter[axis] - minMax.second[axis]);
        }

        collision = squaredDistance <= (sph.GetRadius() * sph.GetRadius()); /* Collision will happen if the (squared) distance between the sphere
                                                                                     and the box is inferior to the (squared) radius of the sphere */

        return std::pair<float, bool>(squaredDistance, collision);
    }

    bool PointToSphere(const Point3D& dot, const Sphere& sph)
    {
        float distanceSquared = dot.distanceSquaredFrom(sph.GetCenter());

        return distanceSquared < (sph.GetRadius() * sph.GetRadius());
    }

    bool PointToAABB(const Point3D& dot, const Box& box)
    {
        std::pair<Vertex3D, Vertex3D> minMax = box.GetMinMax();    /* Gets minimum and maximum vertices of the box */

        return (
            dot.m_x >= minMax.first.m_x &&
            dot.m_x <= minMax.second.m_x &&
            dot.m_y >= minMax.first.m_y &&
            dot.m_y <= minMax.second.m_y &&
            dot.m_z >= minMax.first.m_z &&
            dot.m_z <= minMax.second.m_z);
    }

    bool AABBToAABB(const Box& alpha, const Box& beta)
    {
        std::pair<Vertex3D, Vertex3D> minMax1 = alpha.GetMinMax();  /* Gets minimum and maximum vertices of the first box */
        std::pair<Vertex3D, Vertex3D> minMax2 = beta.GetMinMax();   /* Gets minimum and maximum vertices of the second box */

        for (int axis = 0; axis < AABB_NORMAL_AXIS; axis++)
        {
            /* If there is a gap on at least one axis, there is no collision */
            if (!(minMax1.first[axis] <= minMax2.second[axis] && minMax2.first[axis] <= minMax1.second[axis]))
            {
                return false;
            }
        }

        return true;
    }
}
