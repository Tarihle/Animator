#include "LibMath/Quaternion.h"

namespace LibMath
{
/* OPERATORS */

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
	Radian theta = q.getVecPart().angleFrom(r.getVecPart());

	return q * std::sin(theta.radian() * (1 - t)) + r * std::sin(theta.radian() * t) / std::sin(theta.radian());
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

	return Mat4({ aSquared + bSquared - cSquared - dSquared, 2 * (bc - ad), 2 * (ac + bd), 0.f, 2 * (ad + bc),
				  aSquared - bSquared + cSquared - dSquared, 2 * (cd - ab), 0.f, 2 * (bd - ac), 2 * (ab + cd),
				  aSquared - bSquared - cSquared + dSquared, 0.f, 0.f, 0.f, 0.f, 1.f });
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
