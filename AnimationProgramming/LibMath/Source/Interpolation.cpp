#include "LibMath/Interpolation.h"

namespace LibMath
{
	float Lerp(float& alpha, float& bravo, float ratio)
	{
		if (ratio == 0)
			return alpha;
		else if (ratio == 1.f)
			return bravo;

		return (bravo - alpha) * ratio + alpha;
	}

	Vec2 Lerp(Vec2& charlie, Vec2& delta, float ratio)
	{
		if (ratio == 0)
			return charlie;
		else if (ratio == 1.f)
			return delta;

		return (delta - charlie) * ratio + charlie;
	}

	Vec3 Lerp(Vec3& echo, Vec3& foxtrot, float ratio)
	{
		if (ratio == 0)
			return echo;
		else if (ratio == 1.f)
			return foxtrot;

		return (foxtrot - echo) * ratio + echo;
	}

	Vec4 Lerp(Vec4& kilo, Vec4& lima, float ratio)
	{
		if (ratio == 0)
			return kilo;
		else if (ratio == 1.f)
			return lima;

		return (lima - kilo) * ratio + kilo;
	}

	Radian Lerp(Radian& mike, Radian& november, float ratio)
	{
		if (ratio == 0)
			return mike;
		else if (ratio == 1.f)
			return november;

		return Radian((november.raw() - mike.raw()) * ratio + mike.raw());
	}

	Degree Lerp(Degree& oscar, Degree& papa, float ratio)
	{
		if (ratio == 0)
			return oscar;
		else if (ratio == 1.f)
			return papa;

		return Degree((papa.raw() - oscar.raw()) * ratio + oscar.raw());
	}

	Vec2 Bilerp(Vec2& quebec, Vec2& romeo, Vec2& ratio)
	{
		return Vec2(Lerp(quebec.m_x, romeo.m_x, ratio.m_x), Lerp(quebec.m_y, romeo.m_y, ratio.m_y));
	}
}
