#include "LibMath/Quaternion.h"
#include "LibMath/Interpolation.h"

namespace LibMath
{
/* OPERATORS */
//bool Quaternion::operator==(Quaternion const& other) const
//{
//	return (
//		AlmostEqual(m_a, other.m_a) && AlmostEqual(m_b, other.m_b) && AlmostEqual(m_c, other.m_c) && AlmostEqual(m_d, other.m_d));
//}
//
//bool Quaternion::operator!=(Quaternion const& other) const
//{
//	return !(
//		AlmostEqual(m_a, other.m_a) && AlmostEqual(m_b, other.m_b) && AlmostEqual(m_c, other.m_c) && AlmostEqual(m_d, other.m_d));
//}

float& Quaternion::operator[](int index)
{
	switch (index)
	{
	case 0:
		return m_a;
	case 1:
		return m_b;
	case 2:
		return m_c;
	case 3:
		return m_d;
	default:
		throw std::logic_error("Index must be in range [0, 3]");
	}
}

float Quaternion::operator[](int index) const
{

	switch (index)
	{
	case 0:
		return m_a;
	case 1:
		return m_b;
	case 2:
		return m_c;
	case 3:
		return m_d;
	default:
		throw std::logic_error("Index must be in range [0, 3]");
	}
}

Quaternion& Quaternion::operator+=(Quaternion const& rhs)
{
	m_a += rhs.m_a;
	m_b += rhs.m_b;
	m_c += rhs.m_c;
	m_d += rhs.m_d;

	return *this;
}

Quaternion& Quaternion::operator-=(Quaternion const& rhs)
{
	m_a -= rhs.m_a;
	m_b -= rhs.m_b;
	m_c -= rhs.m_c;
	m_d -= rhs.m_d;

	return *this;
}

Quaternion& Quaternion::operator*=(float scalar)
{
	m_a *= scalar;
	m_b *= scalar;
	m_c *= scalar;
	m_d *= scalar;

	return *this;
}

Quaternion& Quaternion::operator*=(Quaternion const& rhs)
{
	Quaternion copy(*this);

	m_a = copy.m_a * rhs.m_a - copy.m_b * rhs.m_b - copy.m_c * rhs.m_c - copy.m_d * rhs.m_d;
	m_b = copy.m_a * rhs.m_b + copy.m_b * rhs.m_a + copy.m_c * rhs.m_d - copy.m_d * rhs.m_c;
	m_c = copy.m_a * rhs.m_c + copy.m_c * rhs.m_a + copy.m_d * rhs.m_b - copy.m_b * rhs.m_d;
	m_d = copy.m_a * rhs.m_d + copy.m_d * rhs.m_a + copy.m_b * rhs.m_c - copy.m_c * rhs.m_b;

	return *this;
}

Quaternion& Quaternion::operator/=(float scalar)
{
	m_a /= scalar;
	m_b /= scalar;
	m_c /= scalar;
	m_d /= scalar;

	return *this;
}

Quaternion& Quaternion::operator/=(Quaternion const& rhs)
{
	return ((*this *= conjugate(rhs)) /= rhs.magnitudeSquared());
}

Quaternion::operator Mat4(void) const
{
	return Mat4({ m_a, -m_b, -m_c, -m_d, m_b, m_a, -m_d, m_c, m_c, m_d, m_a, -m_b, m_d, -m_c, m_b, m_a });
}

Quaternion::operator Vec4(void) const
{
	return Vec4(m_b, m_c, m_d, m_a);
}

/* FUNCTIONS */

float Quaternion::magnitude(void) const
{
	return std::sqrtf(std::powf(m_a, 2) + std::powf(m_b, 2) + std::powf(m_c, 2) + std::powf(m_d, 2));
}

float Quaternion::magnitudeSquared(void) const
{
	return (std::powf(m_a, 2) + std::powf(m_b, 2) + std::powf(m_c, 2));
}

Quaternion& Quaternion::toConjugate(void)
{
	m_b *= -1;
	m_c *= -1;
	m_d *= -1;

	return *this;
}

bool Quaternion::isUnitQuaternion(void) const
{
	return magnitude() == 1.f;
}

Quaternion& Quaternion::toUnitQuaternion(void)
{
	*this /= magnitude();
	return *this;
}

Vec3 Quaternion::getVecPart(void) const
{
	return Vec3(m_b, m_c, m_d);
}

/* OUT-OF-CLASS FUNCTIONS */

Quaternion conjugate(Quaternion const& quat)
{
	return Quaternion(quat.m_a, -quat.m_b, -quat.m_c, -quat.m_d);
}

Quaternion normalize(Quaternion const& quat)
{
	return (quat / quat.magnitude());
}

Quaternion slerp(Quaternion const& q, Quaternion const& r, float t)
{
	if (q == r || t <= 0.f)
	{
		return q;
	}
	else if (t >= 1.f)
	{
		return r;
	}

	//Quaternion z = r;
	//float cosTheta = Vec4(q).dot(r);

	//// If cosTheta < 0, the interpolation will take the long way around the sphere.
	//// To fix this, one quat must be negated.
	//if (cosTheta < 0.f)
	//{
	//	z = conjugate(r);
	//	cosTheta = -cosTheta;
	//}

	//// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
	//if (cosTheta >= 1.f)
	//{
	//	// Linear interpolation
	//	return Quaternion(Lerp(q.m_a, z.m_a, t), Lerp(q.m_b, z.m_b, t), Lerp(q.m_c, z.m_c, t), Lerp(q.m_d, z.m_d, t));
	//}
	//else
	//{
	//	float angle = std::acos(cosTheta);
	//	return (std::sin((1.f - t) * angle) * q + std::sin(t * angle) * z) / std::sin(angle);
	//}
	float		cosTheta = Vec4(q).dot(r);
	float const sign = cosTheta >= 0.f ? 1.f : -1.f;
	cosTheta *= sign;

	float qScale = 1.f - t;
	float rScale = t * sign;

	if (cosTheta < 1.f)
	{
		float const theta = std::acos(cosTheta);
		float const invSin = 1.f / std::sin(theta);
		qScale = std::sin(qScale * theta) * invSin;
		rScale = std::sin(rScale * theta) * invSin;
	}

	return q * qScale + r * rScale;
}

Vec4 rotatePointVec4(Quaternion const& rot, Vec4 const& point)
{
	Quaternion conjugate;
	if (point.m_w != 0.f)
	{
		throw std::logic_error("point w must be 0");
	}

	if (rot.isUnitQuaternion())
	{
		conjugate = LibMath::conjugate(rot);
	}
	else
	{
		conjugate = LibMath::conjugate(LibMath::normalize(rot));
	}

	Quaternion result = rot * point.toQuaternion();
	result *= conjugate;

	return Vec4(result.m_b, result.m_c, result.m_d, result.m_a);
}

Vec3 rotatePointVec3(Quaternion const& rot, Vec3 const& point)
{
	Quaternion conjugate;
	Quaternion pointQuat(0.f, point);

	if (rot.isUnitQuaternion())
	{
		conjugate = LibMath::conjugate(rot);
	}
	else
	{
		conjugate = LibMath::conjugate(LibMath::normalize(rot));
	}

	Quaternion result = rot * pointQuat;
	result *= conjugate;

	return Vec3(result.m_b, result.m_c, result.m_d);
}

Mat4 toMat4(Quaternion const& quat)
{
	return Mat4({ quat.m_a, -quat.m_b, -quat.m_c, -quat.m_d, quat.m_b, quat.m_a, -quat.m_d, quat.m_c, quat.m_c, quat.m_d, quat.m_a,
				  -quat.m_b, quat.m_d, -quat.m_c, quat.m_b, quat.m_a });
}

Mat4 toRotationMat4(Quaternion const& quat)
{
	Quaternion copy(quat);

	if (!copy.isUnitQuaternion())
	{
		copy /= copy.magnitude();
	}

	float aSquared = copy.m_a * copy.m_a;
	float bSquared = copy.m_b * copy.m_b;
	float cSquared = copy.m_c * copy.m_c;
	float dSquared = copy.m_d * copy.m_d;

	float ab = copy.m_a * copy.m_b;
	float ac = copy.m_a * copy.m_c;
	float ad = copy.m_a * copy.m_d;

	float bc = copy.m_b * copy.m_c;
	float bd = copy.m_b * copy.m_d;

	float cd = copy.m_c * copy.m_d;

	Vec4 row1 = { aSquared + bSquared - cSquared - dSquared, 2 * (bc + ad), 2 * (bd - ac), 0.f };
	Vec4 row2 = { 2 * (bc - ad), aSquared - bSquared + cSquared - dSquared, 2 * (cd + ab), 0.f };
	Vec4 row3 = { 2 * (bd + ac), 2 * (cd - ab), aSquared - bSquared - cSquared + dSquared, 0.f };
	Vec4 row4 = { 0.f, 0.f, 0.f, 1.f };

	return Mat4(row1, row2, row3, row4);
}

/* OUT-OF-CLASS OPERATORS */

Quaternion operator+(Quaternion const& lhs, Quaternion const& rhs)
{
	return Quaternion(lhs.m_a + rhs.m_a, lhs.m_b + rhs.m_b, lhs.m_c + rhs.m_c, lhs.m_d + rhs.m_d);
}

Quaternion operator-(Quaternion const& lhs, Quaternion const& rhs)
{
	return Quaternion(lhs.m_a - rhs.m_a, lhs.m_b - rhs.m_b, lhs.m_c - rhs.m_c, lhs.m_d - rhs.m_d);
}

Quaternion operator*(Quaternion const& lhs, float scalar)
{
	return Quaternion(lhs.m_a * scalar, lhs.m_b * scalar, lhs.m_c * scalar, lhs.m_d * scalar);
}

Quaternion operator*(float scalar, Quaternion const& rhs)
{
	return Quaternion(rhs.m_a * scalar, rhs.m_b * scalar, rhs.m_c * scalar, rhs.m_d * scalar);
}

Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs)
{
	Quaternion copy(lhs);
	return copy *= rhs;
}

Quaternion operator/(Quaternion const& lhs, float scalar)
{
	return Quaternion(lhs.m_a / scalar, lhs.m_b / scalar, lhs.m_c / scalar, lhs.m_d / scalar);
}

Quaternion operator/(float scalar, Quaternion const& rhs)
{
	return Quaternion(rhs.m_a / scalar, rhs.m_b / scalar, rhs.m_c / scalar, rhs.m_d / scalar);
}

Quaternion operator/(Quaternion const& lhs, Quaternion const& rhs)
{
	Quaternion copy(lhs);
	return copy /= rhs;
}

} // namespace LibMath
