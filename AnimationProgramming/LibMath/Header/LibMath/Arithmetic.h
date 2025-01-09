#ifndef __LIBMATH__ARITHMETIC_H__
#define __LIBMATH__ARITHMETIC_H__

#define EPSILON 0.000001f
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

namespace LibMath
{
	///<summary>Checks if 2 floats are within 10^-6 of each other.</summary>
	///<param name="alpha">: First float.</param>
	///<param name="beta">: Second float.</param>
	///<returns>True if floats are close enough, false if not.</returns>
	bool	AlmostEqual(float alpha, float beta);
	
	///<summary>Rounds up a value.</summary>
	///<param name="value">: Value to round up.</param>
	///<returns>Lowest integer value higher or equal to parameter.</returns>
	int		Ceiling(float value);
	
	///<summary>Limits a value to a range.</summary>
	///<param name="value">: Value to limit.</param>
	///<param name="min">: Minimum of the range.</param>
	///<param name="max">: Maximum of the range.</param>
	///<returns>Parameter limited by the given range.</returns>
	float	Clamp(float value, float min, float max);
	
	///<summary>Rounds down a value.</summary>
	///<param name="value">: Value to round down.</param>
	///<returns>Highest integer value lower or equal to parameter.</returns>
	int		Floor(float value);
	
	///<summary>Calculates the Power of a number, given the exponent.</summary>
	///<param name="base">: Value to multiply by itself.</param>
	///<param name="exponent">: How many times the base will be multiplied by itself.</param>
	///<returns>"base"^"exponent".</returns>
	float	Power(float base, int exponent);
	
	///<summary>Calculates the square root of a number.</summary>
	///<param name="value">: Value to calculate the square root of.</param>
	///<returns>Square root of the parameter.</returns>
	float	SquareRoot(float value);
	
	///<summary>Calculates the value's equivalent inside of the given range.</summary>
	///<param name="value">: Value to wrap.</param>
	///<param name="rangeMin">: Minimum of the range.</param>
	///<param name="rangeMax">: Maximum of the range.</param>
	///<returns>Value's equivalent inside of the given range.</returns>
	float	Wrap(float value, float rangeMin, float rangeMax);
	
	///<summary>Modulus operation with a float.</summary>
	///<param name="numerator">: Numerator of the euclidian division.</param>
	///<param name="denominator">: Denominator of the euclidian division.</param>
	///<returns>Modulo of a floating point divison.</returns>
	float	FloatMod(float numerator, float denominator);
	
	///<summary>Swaps 2 integers.</summary>
	///<param name="alpha">: First int.</param>
	///<param name="beta">: Second int.</param>
	void	Swap(int& alpha, int& beta);
	
	///<summary>Swaps 2 floats.</summary>
	///<param name="alpha">: First float.</param>
	///<param name="beta">: Second float.</param>
	void	Swap(float& alpha, float& beta);
	
	///<summary>Separates a float into its mantissa and exponent parts.</summary>
	///<param name="value">: Float to deconstruct.</param>
	///<param name="mantissa">: Reference of a float where the mantissa will be placed.</param>
	///<param name="exponent">: Reference of an int where the exponent will be placed.</param>
	void	SeparateFloat(float value, float& mantissa, int& exponent);
	
	///<summary>Constructs a float with a given mantissa and exponent.</summary>
	///<param name="mantissa">: Mantissa of the constructed float.</param>
	///<param name="exponent">: Exponent of the constructed float.</param>
	///<returns>New corresponding float.</returns>
	float	AssembleFloat(float mantissa, int exponent);
}

#endif // !__LIBMATH__ARITHMETIC_H__
