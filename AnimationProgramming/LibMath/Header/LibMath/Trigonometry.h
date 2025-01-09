#ifndef __LIBMATH__TRIGONOMETRY_H__
#define __LIBMATH__TRIGONOMETRY_H__

#include "Angle/Radian.h"

namespace LibMath
{
	extern float const g_pi;		// useful constant pi -> 3.141592...
	extern float const g_2pi;		// useful constant pi -> 3.141592...
	extern float const g_halfpi;	// useful constant pi -> 3.141592...


	///<summary>Calculates the sine of an angle by Taylor series approximation.</summary>
	///<param name="angle">: Angle.</param>
	///<returns>Sine of the angle.</returns>
	float	sin(Radian angle);
	
	///<summary>Calculates the cosine of an angle by Taylor series approximation.</summary>
	///<param name="angle">: .</param>
	///<returns>Cosine of the angle.</returns>
	float	cos(Radian angle);

	///<summary>Calculates the tangeant of an angle by Taylor series approximation.</summary>
	///<param name="angle">: .</param>
	///<returns>Tangeant of the angle.</returns>
	float	tan(Radian angle);

	///<summary>Calculates the arcsine of a value between 0 and 1.</summary>
	///<param name="value">: .</param>
	///<returns>Corresponding angle.</returns>
	Radian	asin(float value);

	///<summary>Calculates the arccosine of a value between 0 and 1.</summary>
	///<param name="value">: .</param>
	///<returns>Corresponding angle.</returns>
	Radian	acos(float value);

	///<summary>Calculates the arctangeant of a value between 0 and 1.</summary>
	///<param name="value">: .</param>
	///<returns>Corresponding angle.</returns>
	Radian	atan(float value);

	///<summary>Calculates the arctangeant of a value between 0 and 1 and corrects the angle.</summary>
	///<param name="y">: Vertical component.</param>
	///<param name="x">: Horizontal component.</param>
	///<returns>Corresponding angle.</returns>
	Radian	atan2(float y, float x);
}

#endif // !__LIBMATH__TRIGONOMETRY_H__
