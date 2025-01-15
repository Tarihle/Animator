#ifndef __LIBMATH__INTERPOLATION_H__
#define __LIBMATH__INTERPOLATION_H__

#include "LibMath/Angle.h"
#include "LibMath/Vector.h"

namespace LibMath
{
	/////<summary>Calculates the linear interpolation between 2 floats.</summary>
	/////<param name="alpha">: First float.</param>
	/////<param name="bravo">: Second float.</param>
	/////<param name="ratio">: Decimal representation of a percentage.</param>
	/////<returns>Resulting float.<returns>
	//float	Lerp(float& alpha, float& bravo, float ratio);
	///<summary>Calculates the linear interpolation between 2 floats.</summary>
	///<param name="alpha">: First float.</param>
	///<param name="bravo">: Second float.</param>
	///<param name="ratio">: Decimal representation of a percentage.</param>
	///<returns>Resulting float.<returns>
	float	Lerp(const float alpha, const float bravo, float ratio);

	/////<summary>Calculates the linear interpolation between 2 Vec2s.</summary>
	/////<param name="charlie">: First Vec2.</param>
	/////<param name="delta">: Second Vec2.</param>
	/////<param name="ratio">: Decimal representation of a percentage.</param>
	/////<returns>Resulting Vec2.<returns>
	//Vec2	Lerp(Vec2& charlie, Vec2& delta, float ratio);

	///<summary>Calculates the linear interpolation between 2 Vec3s.</summary>
	///<param name="echo">: First Vec3.</param>
	///<param name="foxtrot">: Second Vec3.</param>
	///<param name="ratio">: Decimal representation of a percentage.</param>
	///<returns>Resulting Vec3.<returns>
	Vec3	Lerp(Vec3& echo, Vec3& foxtrot, float ratio);

	///<summary>Calculates the linear interpolation between 2 Vec3s.</summary>
	///<param name="echo">: First Vec3.</param>
	///<param name="foxtrot">: Second Vec3.</param>
	///<param name="ratio">: Decimal representation of a percentage.</param>
	///<returns>Resulting Vec3.<returns>
	Vec3	Lerp(const Vec3 echo, const Vec3 foxtrot, float ratio);

	///<summary>Calculates the linear interpolation between 2 Vec4s.</summary>
	///<param name="kilo">: First Vec4.</param>
	///<param name="lima">: Second Vec4.</param>
	///<param name="ratio">: Decimal representation of a percentage.</param>
	///<returns>Resulting Vec4.<returns>
	Vec4	Lerp(Vec4& kilo, Vec4& lima, float ratio);

	///<summary>Calculates the linear interpolation between 2 Radians.</summary>
	///<param name="mike">: First Radian.</param>
	///<param name="november">: Second Radian.</param>
	///<param name="ratio">: Decimal representation of a percentage.</param>
	///<returns>Resulting Radian.<returns>
	Radian	Lerp(Radian& mike, Radian& november, float ratio);

	///<summary>Calculates the linear interpolation between 2 Degrees.</summary>
	///<param name="oscar">: First Degree.</param>
	///<param name="papa">: Second Degree.</param>
	///<param name="ratio">: Decimal representation of a percentage.</param>
	///<returns>Resulting Degree.<returns>
	Degree	Lerp(Degree& oscar, Degree& papa, float ratio);

	///<summary>Calculates the bilinear interpolation between 2 Vec2s.</summary>
	///<param name="quebec">: First Vec2.</param>
	///<param name="romeo">: Second Vec2.</param>
	///<param name="ratio">: Decimal representations of percentages (x and y).</param>
	///<returns>Resulting Vec2.<returns>
	Vec2	Bilerp(Vec2& quebec, Vec2& romeo, Vec2& ratio);
}

#endif // !__LIBMATH__INTERPOLATION_H__
