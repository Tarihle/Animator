#ifndef __LIBMATH__INTERSECTION__2D__COLLISION_H__
#define __LIBMATH__INTERSECTION__2D__COLLISION_H__

#include <vector>

#include "LibMath/Intersection/2D/Circle.h"
#include "LibMath/Intersection/2D/Rectangle.h"
#include "LibMath/Intersection/2D/Line.h"

namespace LibMath
{
	bool CollisionCheck(const Circle& alpha, const Circle& beta);

	bool CollisionCheck(const Circle& cir, const Rectangle& rec);

	bool CollisionCheck(const Circle& cir, const Line& lin);

	bool CollisionCheck(const Line& alpha, const Line& beta);
	
	bool CollisionCheck(const Line& lin, const Rectangle& rec);

	bool CollisionCheckAABB(const Rectangle& alpha, const Rectangle& beta);

	bool CollisionCheckOBB(const Rectangle& alpha, const Rectangle& beta);

	bool CollisionCheckOBB(std::vector<Vertex2D>& alpha, std::vector<Vertex2D>& beta);

	bool SAT(Vec2& normalVector, std::vector<Vertex2D>& alpha, std::vector<Vertex2D>& beta);

	bool CollisionCheck(const Point2D& dot, const Circle& cir);

	bool CollisionCheck(const Point2D& dot, const Rectangle& rec);

	bool CollisionCheck(const Point2D& dot, const Line& lin);

	////////////////////////////////////////////////////////////////////

	std::vector<Point2D> Intersection(const Circle& alpha, const Circle& beta);

	std::vector<Point2D> Intersection(const Circle& cir, const Rectangle& rec);

	std::vector<Point2D> Intersection(const Circle& cir, const Line& lin);

	Point2D Intersection(const Line& alpha, const Line& beta);

	std::vector<Point2D> Intersection(const Line& lin, const Rectangle& rec);

	std::vector<Point2D> Intersection(const Rectangle& alpha, const Rectangle& beta);
}

#endif // !__LIBMATH__INTERSECTION__2D__COLLISION_H__
