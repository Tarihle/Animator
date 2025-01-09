#include "LibMath/Arithmetic.h"

bool LibMath::AlmostEqual(float alpha, float beta)
{
	return FLOAT_EQ(alpha, beta);
}

int LibMath::Ceiling(float value)
{
	return (int)(value + 1);
}

float LibMath::Clamp(float value, float min, float max)
{
	if (min > max)
	{
		return Clamp(value, max, min);
	}

	if (value >= min && value <= max)
		return value;

	return (value < min ? min : max);
}

int LibMath::Floor(float value)
{
	return (int)value;
}

float LibMath::Power(float base, int exponent)
{
	if (exponent == 0)
		return 1.f;
	else if (base == 0)
		return 0.f;

	float result = base;
	for (int i = 1; i < exponent; i++)
	{
		result *= base;
	}

	return result;
}

float LibMath::SquareRoot(float value)
{
	if (value <= 0)
		return 0;       // if negative number throw an exception?

	int exp = 0;
	float mantissa;
	SeparateFloat(value, mantissa, exp); // extract binary exponent from x
	if (exp & 1) {      // we want exponent to be even
		exp--;
		mantissa *= 2;
	}
	float y = (1 + mantissa) / 2; // first approximation
	float z = 0;
	while (y != z) {    // yes, we CAN compare doubles here!
		z = y;
		y = (y + mantissa / y) / 2;
	}
	return AssembleFloat(y, exp / 2); // multiply answer by 2^(exp/2)}
}

float LibMath::Wrap(float value, float rangeMin, float rangeMax)
{
	if (rangeMin > rangeMax)
	{
		return Wrap(value, rangeMax, rangeMin);
	}
	else if (rangeMin == rangeMax)
		return rangeMin;

	if (value >= rangeMin && value <= rangeMax)
		return value;
	else
	{
		return (value >= 0 ? rangeMin : rangeMax) + LibMath::FloatMod(value, rangeMax - rangeMin);
	}
}

float LibMath::FloatMod(float numerator, float denominator)
{
	return numerator - ((int)(numerator / denominator)) * denominator;
}

void LibMath::Swap(int& alpha, int& beta)
{
	alpha ^= beta;
	beta ^= alpha;
	alpha ^= beta;
}

void LibMath::Swap(float& alpha, float& beta)
{
	float temp = alpha;
	alpha = beta;
	beta = temp;
}

void LibMath::SeparateFloat(float value, float& mantissa, int& exponent)
{
	int binValue = *(int*)&value;

	int temp = binValue & 0x7F800000;

	exponent = temp;

	temp = 0;
	while (exponent > 0)
	{
		temp++;
		exponent >>= 1;
	}
	exponent = temp;

	mantissa = value / Power(2.f, exponent);
}

float LibMath::AssembleFloat(float mantissa, int exponent)
{
	return mantissa * Power(2.f, exponent);
}
