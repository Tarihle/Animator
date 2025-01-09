#include "LibMath/Vector/Vec4.h"
#include "LibMath/Vector/Vec3.h"
#include "LibMath/Vector/Vec2.h"
#include "LibMath/Quaternion.h"

#include <string>
#include <sstream>

namespace LibMath
{
	/* STATIC FUNCTIONS */

	Vec4 Vec4::zero() { return Vec4(); }

	Vec4 Vec4::one() { return Vec4(1.f); }

	/* BASIC FUNCTIONS */

	Radian Vec4::angleFrom(Vec4 const& other) const
	{
		float dot = this->dot(other);
		float radian = std::acosf(dot / (this->magnitude() * other.magnitude()));

		return Radian(radian);
	}

	float Vec4::distanceFrom(Vec4 const& other) const
	{
		return std::sqrtf(
			std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2) +
			std::powf(other.m_z - this->m_z, 2) +
			std::powf(other.m_w - this->m_w, 2)
		);
	}

	float Vec4::distanceSquaredFrom(Vec4 const& other) const
	{
		return (
			std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2) +
			std::powf(other.m_z - this->m_z, 2) +
			std::powf(other.m_w - this->m_w, 2)
		);
	}

	float Vec4::distance2DFrom(Vec4 const& other) const
	{
		return std::sqrtf(
			std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2)
		);
	}

	float Vec4::distance2DSquaredFrom(Vec4 const& other) const
	{
		return (
			std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2)
		);
	}

	float Vec4::dot(Vec4 const& other) const
	{
		return (
			this->m_x * other.m_x +
			this->m_y * other.m_y +
			this->m_z * other.m_z +
			this->m_w * other.m_w
		);
	}

	bool Vec4::isLongerThan(Vec4 const& other) const
	{
		return this->magnitude() > other.magnitude();
	}

	bool Vec4::isShorterThan(Vec4 const& other) const
	{
		return this->magnitude() < other.magnitude();
	}

	bool Vec4::isUnitVector(void) const
	{
		return this->magnitude() == 1.f;
	}

	float Vec4::magnitude(void) const
	{
		return std::sqrtf(
			std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2) +
			std::powf(this->m_z, 2) +
			std::powf(this->m_w, 2)
		);
	}

	float Vec4::magnitudeSquared(void) const
	{
		return (
			std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2) +
			std::powf(this->m_z, 2) +
			std::powf(this->m_w, 2)
		);
	}

	Vec4& Vec4::normalize(void)
	{
		this->operator/=(this->magnitude());

		return *this;
	}

	Vec4 Vec4::normalizenew(void) const
	{
		return Vec4(*this / this->magnitude());
	}

	Vec4& Vec4::projectOnto(Vec4 const& other)
	{
		const float dot = this->dot(other);
		*this = other * Vec4(dot / other.magnitudeSquared());
		return *this;
	}

	Vec4& Vec4::reflectOnto(Vec4 const& other)
	{
		LibMath::Vec4 unitOther;

		if (!other.isUnitVector())
			unitOther = other.normalizenew();
		else
			unitOther = other;

		*this -= unitOther * unitOther.dot(*this) * 2;

		return *this;
	}

	Vec4& Vec4::scale(Vec4 const& other)
	{
		*this *= other;

		return *this;
	}

	Vec4& Vec4::translate(Vec4 const& other)
	{
		*this += other;

		return *this;
	}

	std::string Vec4::string(void) const
	{
		std::stringstream stream;
		stream << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "," << this->m_w << "}";
		return stream.str();
	}

	std::string Vec4::stringLong(void) const
	{
		std::stringstream stream;
		stream << "Vector4{ x:" << this->m_x << ", y:" << this->m_y << ", z:" << this->m_z << ", w:" << this->m_w << " }";
		return stream.str();
	}

	Quaternion Vec4::toQuaternion(void) const
	{
		return Quaternion(this->m_w, this->m_x, this->m_y, this->m_z);
	}


	/* OPERATORS */

	float& Vec4::operator[](int index)
	{
		switch (index)
		{
		case 0: return this->m_x;
		case 1: return this->m_y;
		case 2: return this->m_z;
		case 3: return this->m_w;
		default: throw std::logic_error("Index must be in range [0, 4[");
		}
	}

	float Vec4::operator[](int index) const
	{
		switch (index)
		{
		case 0: return this->m_x;
		case 1: return this->m_y;
		case 2: return this->m_z;
		case 3: return this->m_w;
		default: throw std::logic_error("Index must be in range [0, 4[");
		}
	}

	Vec4& Vec4::operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		m_z *= scalar;
		m_w *= scalar;

		return *this;
	}

	Vec4& Vec4::operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		m_z /= scalar;
		m_w /= scalar;

		return *this;
	}

	Vec4::operator Vec2(void) const
	{
		return Vec2(this->m_x, this->m_y);
	}

	Vec4::operator Vec3(void) const
	{
		return Vec3(this->m_x, this->m_y, this->m_z);
	}

	bool operator==(Vec4 const& lhs, Vec4 const& rhs)
	{
		return (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y && lhs.m_z == rhs.m_z && lhs.m_w == rhs.m_w);
	}

	bool operator!=(Vec4 const& lhs, Vec4 const& rhs)
	{
		return (lhs.m_x != rhs.m_x || lhs.m_y != rhs.m_y || lhs.m_z != rhs.m_z || lhs.m_w != rhs.m_w);
	}

	Vec4 operator-(Vec4 const& other)
	{
		return Vec4(-other.m_x, -other.m_y, -other.m_z, -other.m_w);
	}

	Vec4 operator+(Vec4 const& lhs, Vec4 const& rhs)
	{
		return Vec4(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z, lhs.m_w + rhs.m_w);
	}

	Vec4 operator-(Vec4 const& lhs, Vec4 const& rhs)
	{
		return Vec4(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z, lhs.m_w - rhs.m_w);
	}

	Vec4 operator*(Vec4 const& lhs, Vec4 const& rhs)
	{
		return Vec4(lhs.m_x * rhs.m_x, lhs.m_y * rhs.m_y, lhs.m_z * rhs.m_z, lhs.m_w * rhs.m_w);
	}

	Vec4 operator*(Vec4 const& lhs, float scalar)
	{
		return Vec4(lhs.m_x * scalar, lhs.m_y * scalar, lhs.m_z * scalar, lhs.m_w * scalar);
	}

	Vec4 operator/(Vec4 const& lhs, Vec4 const& rhs)
	{
		return Vec4(lhs.m_x / rhs.m_x, lhs.m_y / rhs.m_y, lhs.m_z / rhs.m_z, lhs.m_w / rhs.m_w);
	}

	Vec4 operator/(Vec4 const& lhs, float scalar)
	{
		return Vec4(lhs.m_x / scalar, lhs.m_y / scalar, lhs.m_z / scalar, lhs.m_w / scalar);
	}

	Vec4& operator+=(Vec4& lhs, Vec4 const& rhs)
	{
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;
		lhs.m_z += rhs.m_z;
		lhs.m_w += rhs.m_w;

		return lhs;
	}

	Vec4& operator-=(Vec4& lhs, Vec4 const& rhs)
	{
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;
		lhs.m_z -= rhs.m_z;
		lhs.m_w -= rhs.m_w;

		return lhs;
	}

	Vec4& operator*=(Vec4& lhs, Vec4 const& rhs)
	{
		lhs.m_x *= rhs.m_x;
		lhs.m_y *= rhs.m_y;
		lhs.m_z *= rhs.m_z;
		lhs.m_w *= rhs.m_w;

		return lhs;
	}

	Vec4& operator/=(Vec4& lhs, Vec4 const& rhs)
	{
		lhs.m_x /= rhs.m_x;
		lhs.m_y /= rhs.m_y;
		lhs.m_z /= rhs.m_z;
		lhs.m_w /= rhs.m_w;

		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, Vec4 const& other)
	{
		return os << other.string();
	}

	std::istream& operator>>(std::istream& is, Vec4& output)
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