#include "LibMath/Intersection/2D/Collision2D.h"

namespace LibMath
{
    bool CollisionCheck(const Circle& alpha, const Circle& beta)
	{
		float distanceBetweenCenter = (beta.GetCenter() - alpha.GetCenter()).magnitudeSquared();

		float sumRadii = alpha.GetRadius() + beta.GetRadius();

		if (distanceBetweenCenter <= (sumRadii * sumRadii))
			return true;

		return false;
	}

	bool CollisionCheck(const Circle& cir, const Rectangle& rec)
	{
		std::vector<Line> sides = rec.GetSides();

		for (int i = 0; i < 4; i++)
		{
			if (CollisionCheck(cir, sides[i]))
				return true;
		}

		return false;
	}

	bool CollisionCheck(const Circle& cir, const Line& lin)
	{
		/* Fetching */
		Point2D CircleCenter = cir.GetCenter();
		Point2D LineStart = lin.GetStart();
		Point2D LineEnd = lin.GetEnd();

		float dot = ((CircleCenter.m_x - LineStart.m_x) * (LineEnd.m_x - LineStart.m_x)) +
			((CircleCenter.m_y - LineStart.m_y) * (LineEnd.m_y - LineStart.m_y)) /
			lin.LengthSquared();

		Point2D closest
		{
			LineStart.m_x + (dot * (LineEnd.m_x - LineStart.m_x)),
			LineStart.m_y + (dot * (LineEnd.m_y - LineStart.m_y))
		};

		Vec2 LineCenter(closest - CircleCenter);

		if (LineCenter.magnitudeSquared() <= cir.GetRadius() * cir.GetRadius())
			return true;

		return false;
	}

	bool CollisionCheck(const Line& alpha, const Line& beta)
	{
		float firstDistance = ((beta.GetEnd().m_x - beta.GetStart().m_x) * (alpha.GetStart().m_y - beta.GetStart().m_y) -
			(beta.GetEnd().m_y - beta.GetStart().m_y) * (alpha.GetStart().m_x - beta.GetStart().m_x)) /
			((beta.GetEnd().m_y - beta.GetStart().m_y) * (alpha.GetEnd().m_x - alpha.GetStart().m_x) -
				(beta.GetEnd().m_x - beta.GetStart().m_x) * (alpha.GetEnd().m_y - alpha.GetStart().m_y));

		float secondDistance = ((alpha.GetEnd().m_x - alpha.GetStart().m_x) * (alpha.GetStart().m_y - beta.GetStart().m_y) -
			(alpha.GetEnd().m_y - alpha.GetStart().m_y) * (alpha.GetStart().m_x - beta.GetStart().m_x)) /
			((beta.GetEnd().m_y - beta.GetStart().m_y) * (alpha.GetEnd().m_x - alpha.GetStart().m_x) -
				(beta.GetEnd().m_x - beta.GetStart().m_x) * (alpha.GetEnd().m_y - alpha.GetStart().m_y));

		if (firstDistance >= 0 && firstDistance <= 1 && secondDistance >= 0 && secondDistance <= 1)
			return true;

		return false;
	}

	bool CollisionCheck(const Line& lin, const Rectangle& rec)
	{
		std::vector<Line> sides = rec.GetSides();

		for (int i = 0; i < 4; i++)
		{
			if (CollisionCheck(lin, sides[i]))
				return true;
		}

		return false;
	}

	bool CollisionCheckAABB(const Rectangle& alpha, const Rectangle& beta)
	{
		std::pair<Vertex2D, Vertex2D> alphaMinMax = alpha.GetMinMax();
		std::pair<Vertex2D, Vertex2D> betaMinMax = beta.GetMinMax();

		if (alphaMinMax.first.m_x < betaMinMax.second.m_x &&
			alphaMinMax.first.m_y < betaMinMax.second.m_y &&
			betaMinMax.first.m_x < alphaMinMax.second.m_x &&
			betaMinMax.first.m_y < alphaMinMax.second.m_y)
			return true;

		return false;
	}

	bool CollisionCheckOBB(const Rectangle& alpha, const Rectangle& beta)
	{
		std::vector<Vertex2D> alphaVertices = alpha.GetVertices();
		std::vector<Vertex2D> betaVertices = beta.GetVertices();

		for (int i = 0; i < alphaVertices.size(); ++i)
		{
			LibMath::Vec2 normalVector(alphaVertices[i].m_y, -(alphaVertices[i].m_x));

			if (!SAT(normalVector, alphaVertices, betaVertices))
				return false;
		}

		for (int i = 0; i < betaVertices.size(); ++i)
		{
			LibMath::Vec2 normalVector(betaVertices[i].m_y, -(betaVertices[i].m_y));

			if (!SAT(normalVector, alphaVertices, betaVertices))
				return false;
		}

		return true;
	}

	bool CollisionCheckOBB(std::vector<Vertex2D>& alpha, std::vector<Vertex2D>& beta)
	{
		for (int i = 0; i < alpha.size(); ++i)
		{
			LibMath::Vec2 normalVector(alpha[i].m_y, -(alpha[i].m_x));

			if (!SAT(normalVector, alpha, beta))
				return false;
		}

		for (int i = 0; i < beta.size(); ++i)
		{
			LibMath::Vec2 normalVector(beta[i].m_y, -(beta[i].m_y));

			if (!SAT(normalVector, alpha, beta))
				return false;
		}

		return true;
	}

	bool SAT(Vec2& normalVector, std::vector<Vertex2D>& alpha, std::vector<Vertex2D>& beta)
	{
		float   maxAlpha = normalVector.dot(alpha[0]), minAlpha = normalVector.dot(alpha[0]);
		float   maxBeta = normalVector.dot(beta[0]), minBeta = normalVector.dot(beta[0]);
		float   result = 0.f;

		for (unsigned int i = 1; i < alpha.size(); i++)
		{
			result = normalVector.dot(alpha[i]);

			if (result > maxAlpha)
			{
				maxAlpha = result;
				continue;
			}
			else if (result < minAlpha)
			{
				minAlpha = result;
			}
		}

		for (unsigned int i = 1; i < beta.size(); i++)
		{
			result = normalVector.dot(beta[i]);
			if (result > maxBeta)
			{
				maxBeta = result;
				continue;
			}
			else if (result < minBeta)
			{
				minBeta = result;
			}
		}

		if (!(maxAlpha >= minBeta && maxBeta >= minAlpha))
		{
			return false;
		}
			
		return true;
	}

	bool CollisionCheck(const Point2D& dot, const Circle& cir)
	{
		if (LibMath::Vec2(dot - cir.GetCenter()).magnitudeSquared() <= cir.GetRadius() * cir.GetRadius())
			return true;

		return false;
	}

	bool CollisionCheck(const Point2D& dot, const Rectangle& rec)
	{
		std::pair<Vertex2D, Vertex2D> recMinMax = rec.GetMinMax();

		if (dot.m_x >= recMinMax.first.m_x &&
			dot.m_y >= recMinMax.first.m_y &&
			dot.m_x <= recMinMax.second.m_x &&
			dot.m_y <= recMinMax.second.m_y)
			return true;

		return false;
	}

	bool CollisionCheck(const Point2D& dot, const Line& lin)
	{
		float LineSlope = lin.GetSlope();
		float b = -LineSlope * lin.GetStart().m_x + lin.GetStart().m_y;	/* retrieved from Line equation y = mx + b */

		if ((dot.m_x * LineSlope + b) == dot.m_y)
			return true;

		return false;
	}
}
