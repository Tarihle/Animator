#include "LibMath/Vector/Vec2.h"
#include "LibMath/Vector/Vec3.h"
#include "LibMath/Vector/Vec4.h"
#include "LibMath/Arithmetic.h"

#include <string>
#include <sstream>

namespace LibMath
{
	/* STATIC FUNCTIONS */

	Vec3 Vec3::zero() { return Vec3(); }

	Vec3 Vec3::one() { return Vec3(1.f); }

	Vec3 Vec3::up() { return Vec3(0.f, 1.f, 0.f); }

	Vec3 Vec3::down() { return Vec3(0.f, -1.f, 0.f); }

	Vec3 Vec3::left() { return Vec3(-1.f, 0.f, 0.f); }

	Vec3 Vec3::right() { return Vec3(1.f, 0.f, 0.f); }

	Vec3 Vec3::front() { return Vec3(0.f, 0.f, 1.f); }

	Vec3 Vec3::back()
	{
		return Vec3(0.f, 0.f, -1.f);
	}

	float Vec3::dot(Vec3 const& u, Vec3 const& v)
	{
		return (u.m_x * v.m_x + u.m_y * v.m_y + u.m_z * v.m_z);
	}

	Vec3 Vec3::alternativePerp(Vec3 const& u, Vec3 const& v)
	{
		float y = ((v.m_x * u.m_z / u.m_x) - v.m_z) / ((-v.m_x * u.m_y / u.m_x) + v.m_y);
		float x = (-u.m_y * y - u.m_z) / u.m_x;

		return Vec3(x, y, 1.f).normalize();
	}


	/* BASIC FUNCTIONS */

	Radian Vec3::angleFrom(Vec3 const& other) const
	{
		float dot = this->dot(other);
		float radian = std::acosf(Clamp(dot / (this->magnitude() * other.magnitude()), -1.f, 1.f));

		return Radian(radian);
	}

	Radian Vec3::orientedAngleFrom(Vec3 const& other, Vec3 const& axisRef) const
	{
		Radian angle = this->angleFrom(other);

		return axisRef.dot(this->cross(other)) >= 0 ? angle : -angle;
	}

	Vec3 Vec3::cross(Vec3 const& other) const
	{
		return Vec3(m_y * other.m_z - m_z * other.m_y, 
					m_z * other.m_x - m_x * other.m_z, 
					m_x * other.m_y - m_y * other.m_x);
	}

	float Vec3::distanceFrom(Vec3 const& other) const
	{
		return LibMath::SquareRoot(
			LibMath::Power(other.m_x - m_x, 2) +
			LibMath::Power(other.m_y - m_y, 2) +
			LibMath::Power(other.m_z - m_z, 2)
		);
	}

	float Vec3::distanceSquaredFrom(Vec3 const& other) const
	{
		return (
			std::powf(other.m_x - m_x, 2) +
			std::powf(other.m_y - m_y, 2) +
			std::powf(other.m_z - m_z, 2)
		);
	}

	float Vec3::distance2DFrom(Vec3 const& other) const
	{
		return std::sqrtf(
			std::powf(other.m_x - m_x, 2) +
			std::powf(other.m_y - m_y, 2)
		);
	}

	float Vec3::distance2DSquaredFrom(Vec3 const& other) const
	{
		return (
			std::powf(other.m_x - m_x, 2) +
			std::powf(other.m_y - m_y, 2)
			);;
	}

	float Vec3::dot(Vec3 const& other) const
	{
		return (
			m_x * other.m_x +
			m_y * other.m_y +
			m_z * other.m_z
			);
	}

	bool Vec3::isLongerThan(Vec3 const& other) const
	{
		return (magnitude() > other.magnitude());
	}

	bool Vec3::isShorterThan(Vec3 const& other) const
	{
		return (magnitude() < other.magnitude());
	}

	bool Vec3::isUnitVector(void) const
	{
		return magnitude() == 1.f;
	}

	float Vec3::magnitude(void) const
	{
		return std::sqrtf(
			std::powf(m_x, 2) +
			std::powf(m_y, 2) +
			std::powf(m_z, 2)
		);
	}

	float Vec3::magnitudeSquared(void) const
	{
		return (
			std::powf(m_x, 2) +
			std::powf(m_y, 2) +
			std::powf(m_z, 2)
		);
	}

	Vec3& Vec3::normalize(void)
	{
		this->operator/=(this->magnitude());

		return *this;
	}

	Vec3 Vec3::normalizenew(void) const
	{
		return Vec3(*this / (this->magnitude()));
	}

	Vec3& Vec3::projectOnto(Vec3 const& other)
	{
		const float dot = this->dot(other);
		*this = other * Vec3(dot / other.magnitudeSquared());

		return *this;
	}

	Vec3& Vec3::reflectOnto(Vec3 const& other)
	{
		LibMath::Vec3 unitOther;

		if (!other.isUnitVector())
			unitOther = other.normalizenew();
		else
			unitOther = other;

		*this -= unitOther * unitOther.dot(*this) * 2;

		return *this;
	}

	Vec3& Vec3::rotate(Radian z, Radian x, Radian y)
	{
		float cosZ = std::cosf(z.radian(false));
		float sinZ = std::sinf(z.radian(false));

		float cosX = std::cosf(x.radian(false));
		float sinX = std::sinf(x.radian(false));

		float cosY = std::cosf(y.radian(false));
		float sinY = std::sinf(y.radian(false));

		float tempX = m_x * (cosZ * cosY + sinZ * sinX * sinY)
					+ m_y * (-cosZ * sinY + sinZ * sinX * cosY)
					+ m_z * (sinZ * cosX);

		float tempY = m_x * (sinY * cosX)
					+ m_y * (cosY * cosX)
					+ m_z * -sinX;

		float tempZ = m_x * (-sinZ * cosY + cosZ * sinX * sinY)
					+ m_y * (sinZ * sinY + cosZ * sinX * cosY)
					+ m_z * (cosZ * cosX);

		m_x = tempX, m_y = tempY, m_z = tempZ;

		return *this;
	}

	Vec3& Vec3::rotate(Radian r, Vec3 const& other)
	{
		float cosR = std::cosf(r.radian(false));
		float sinR = std::sinf(r.radian(false));

		LibMath::Vec3 unitOther;

		if (!other.isUnitVector())
			unitOther = other.normalizenew();
		else
			unitOther = other;
		
		LibMath::Vec3 temp = (1 - cosR) * unitOther;

		float tempX = m_x * (cosR + temp.m_x * unitOther.m_x)
					+ m_y * (temp.m_y * unitOther.m_x - sinR * unitOther.m_z)
					+ m_z * (temp.m_z * unitOther.m_x + sinR * unitOther.m_y);

		float tempY = m_x * (temp.m_x * unitOther.m_y + sinR * unitOther.m_z)
					+ m_y * (cosR + temp.m_y * unitOther.m_y)
					+ m_z * (temp.m_z * unitOther.m_y - sinR * unitOther.m_x);

		float tempZ = m_x * (temp.m_x * unitOther.m_z - sinR * unitOther.m_y) 
					+ m_y * (temp.m_y * unitOther.m_z + sinR * unitOther.m_x)
					+ m_z * (cosR + temp.m_z * unitOther.m_z);

		m_x = tempX, m_y = tempY, m_z = tempZ;

		return *this;
	}

	Vec3& Vec3::scale(Vec3 const& other)
	{
		*this *= other;

		return *this;
	}

	Vec3& Vec3::translate(Vec3 const& other)
	{
		*this += other;

		return *this;
	}

	std::string Vec3::string(void) const
	{
		std::stringstream stream;
		stream << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "}";
		return stream.str();
	}

	std::string Vec3::stringLong(void) const
	{
		std::stringstream stream;
		stream << "Vector3{ x:" << this->m_x << ", y:" << this->m_y << ", z:" << this->m_z << " }";
		return stream.str();
	}


	/* OPERATORS */

	float& Vec3::operator[](int index)
	{
		switch (index)
		{
		case 0: return m_x;
		case 1: return m_y;
		case 2: return m_z;
		default: throw std::logic_error("Index must be in range [0, 3[");
		}
	}

	float Vec3::operator[](int index) const
	{
		switch (index)
		{
		case 0: return m_x;
		case 1: return m_y;
		case 2: return m_z;
		default: throw std::logic_error("Index must be in range [0, 3[");
		}
	}

	Vec3& Vec3::operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;		
		
		return *this;
	}

	Vec3& Vec3::operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;

		return *this;
	}

	Vec3::operator Vec2(void) const
	{
		return Vec2(m_x, m_y);
	}

	Vec3::operator Vec4(void) const
	{
		return Vec4(m_x, m_y, m_z, 1.f);
	}

	bool operator==(Vec3 const& lhs, Vec3 const& rhs)
	{
		return (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_z == rhs.m_z);
	}

	bool operator!=(Vec3 const& lhs, Vec3 const& rhs)
	{
		return !(lhs == rhs);
	}

	Vec3 operator-(Vec3 const& other)
	{
		return Vec3(-other.m_x, -other.m_y, -other.m_z);
	}

	Vec3 operator+(Vec3 const& lhs, Vec3 const& rhs)
	{
		return Vec3(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z);
	}

	Vec3 operator-(Vec3 const& lhs, Vec3 const& rhs)
	{
		return Vec3(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z);
	}

	Vec3 operator*(Vec3 const& lhs, float scalar)
	{
		return Vec3(lhs.m_x * scalar, lhs.m_y * scalar, lhs.m_z * scalar);
	}

	Vec3 operator*(float scalar, Vec3 const& rhs)
	{
		return Vec3(rhs.m_x * scalar, rhs.m_y * scalar, rhs.m_z * scalar);
	}

	Vec3 operator*(Vec3 const& lhs, Vec3 const& rhs)
	{
		return Vec3(lhs.m_x * rhs.m_x, lhs.m_y * rhs.m_y, lhs.m_z * rhs.m_z);
	}

	Vec3 operator/(Vec3 const& lhs, float scalar)
	{
		return Vec3(lhs.m_x / scalar, lhs.m_y / scalar, lhs.m_z / scalar);
	}

	Vec3 operator/(Vec3 const& lhs, Vec3 const& rhs)
	{
		return Vec3(lhs.m_x / rhs.m_x, lhs.m_y / rhs.m_y, lhs.m_z / rhs.m_z);
	}

	Vec3& operator+=(Vec3& lhs, Vec3 const& rhs)
	{
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;
		lhs.m_z += rhs.m_z;

		return lhs;
	}

	Vec3& operator-=(Vec3& lhs, Vec3 const& rhs)
	{
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;
		lhs.m_z -= rhs.m_z;

		return lhs;
	}

	Vec3& operator*=(Vec3& lhs, Vec3 const& rhs)
	{
		lhs.m_x *= rhs.m_x;
		lhs.m_y *= rhs.m_y;
		lhs.m_z *= rhs.m_z;

		return lhs;
	}

	Vec3& operator/=(Vec3& lhs, Vec3 const& rhs)
	{
		lhs.m_x /= rhs.m_x;
		lhs.m_y /= rhs.m_y;
		lhs.m_z /= rhs.m_z;

		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, Vec3 const& other)
	{
		return os << other.string();
	}

	std::istream& operator>>(std::istream& is, Vec3& output)
	{
		std::string str;

		char c;
		while (is.get(c))
		{
			str += c;
			if (c == '}') break;
		}

		std::string token;
		size_t pos = 0;

		str.erase(0, str.find("{") + 1);
		str.erase(str.find("}"), str.length());
		str += ',';

		int index = 0;
		while ((pos = str.find(",")) != std::string::npos)
		{
			token = str.substr(0, pos);
			float component = std::stof(token);
			output[index++] = component;
			str.erase(0, pos + 1);
		}
		return is;
	}
}