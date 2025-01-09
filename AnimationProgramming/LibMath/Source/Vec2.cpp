#include "LibMath/Vector/Vec2.h"
#include "LibMath/Vector/Vec4.h"

#include <string>
#include <sstream>

#include <exception>
#include <iostream>

namespace LibMath
{
	/* STATIC FUNCTIONS */

	Vec2 Vec2::zero() { return Vec2(); }

	Vec2 Vec2::one() { return Vec2(1.f); }

	Vec2 Vec2::up() { return Vec2(0.f, 1.f); }

	Vec2 Vec2::down() { return Vec2(0.f, -1.f); }

	Vec2 Vec2::left() { return Vec2(-1.f, 0.f); }

	Vec2 Vec2::right() { return Vec2(1.f, 0.f); }

	/* BASIC FUNCTIONS */

	Radian Vec2::angleFrom(Vec2 const& other) const
	{
		float dot = this->dot(other);
		float radian = std::acosf(dot / (this->magnitude() * other.magnitude()));

		return Radian(radian);
	}

	float Vec2::cross(Vec2 const& other) const
	{
		return this->m_x * other.m_y - this->m_y * other.m_x;
	}

	float Vec2::distanceFrom(Vec2 const& other) const
	{
		return std::sqrtf(
			std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2)
		);
	}

	float Vec2::distanceSquaredFrom(Vec2 const& other) const
	{
		return (
			std::powf(other.m_x - this->m_x, 2) +
			std::powf(other.m_y - this->m_y, 2)
		);
	}

	float Vec2::distance2DFrom(Vec2 const& other) const
	{
		return this->distanceFrom(other);
	}

	float Vec2::distance2DSquaredFrom(Vec2 const& other) const
	{
		return this->distanceSquaredFrom(other);
	}

	float Vec2::dot(Vec2 const& other) const
	{
		return (
			this->m_x * other.m_x +
			this->m_y * other.m_y
			);
	}

	bool Vec2::isLongerThan(Vec2 const& other) const
	{
		return (this->magnitude() > other.magnitude());
	}

	bool Vec2::isShorterThan(Vec2 const& other) const
	{
		return (this->magnitude() < other.magnitude());
	}

	bool Vec2::isUnitVector(void) const
	{
		return (this->magnitude() == 1.f);
	}

	float Vec2::magnitude(void) const
	{
		return std::sqrtf(
			std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2)
		);
	}

	float Vec2::magnitudeSquared(void) const
	{
		return (
			std::powf(this->m_x, 2) +
			std::powf(this->m_y, 2)
		);
	}

	Vec2& Vec2::normalize(void)
	{
		this->operator/=(this->magnitude());

		return *this;
	}

	Vec2 Vec2::normalizenew(void) const
	{
		return Vec2(*this / this->magnitude());
	}

	Vec2& Vec2::projectOnto(Vec2 const& other)
	{
		const float dot = this->dot(other);
		*this = other * Vec2(dot / other.magnitudeSquared());
		return *this;
	}

	Vec2& Vec2::reflectOnto(Vec2 const& other)
	{
		LibMath::Vec2 unitOther;

		if (!other.isUnitVector())
			unitOther = other.normalizenew();
		else
			unitOther = other;

		*this -= unitOther * unitOther.dot(*this) * 2;

		return *this;
	}

	Vec2& Vec2::rotate(Radian x, Radian y)
	{
		//this->m_x = this->m_x * std::cosf(y.radian(false));
		//this->m_y = this->m_y * std::cosf(x.radian(false));

		//return *this;

		*this = LibMath::Vec3(*this).rotate(Radian(0), x, y);

		return *this;
	}

	Vec2& Vec2::rotate(Radian r, Vec2 const& other)
	{
		//return this->rotate(
		//	other.m_x > 0.f ? r : Radian(0.f),
		//	other.m_y > 0.f ? r : Radian(0.f)
		//);
		*this = LibMath::Vec3(*this).rotate(r, other);

		return *this;
	}

	Vec2& Vec2::scale(Vec2 const& other)
	{
		*this *= other;

		return *this;
	}

	Vec2& Vec2::translate(Vec2 const& other)
	{
		*this += other;

		return *this;
	}

	std::string Vec2::string(void) const
	{
		std::stringstream stream;
		stream << "{" << this->m_x << "," << this->m_y << "}";
		return stream.str();
	}

	std::string Vec2::stringLong(void) const
	{
		std::stringstream stream;
		stream << "Vector2{ x:" << this->m_x << ", y:" << this->m_y << " }";
		return stream.str();
	}


	/* OPERATORS */

	float& Vec2::operator[](int index)
	{
		switch (index)
		{
		case 0: return this->m_x;
		case 1: return this->m_y;
		default: throw std::logic_error("Index must be in range [0, 2[");
		}
	}

	float Vec2::operator[](int index) const
	{
		switch (index)
		{
		case 0: return this->m_x;
		case 1: return this->m_y;
		default: throw std::logic_error("Index must be in range [0, 2[");
		}
	}

	Vec2& Vec2::operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;

		return *this;
	}

	Vec2& Vec2::operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;

		return *this;
	}

	Vec2::operator Vec3(void) const
	{
		return Vec3(this->m_x, this->m_y, 1.0f);
	}

	Vec2::operator Vec4(void) const
	{
		return Vec4(this->m_x, this->m_y, 1.0f, 1.0f);
	}

	bool operator==(Vec2 const& lhs, Vec2 const& rhs)
	{
		return (lhs.m_x == rhs.m_x && lhs.m_y == rhs.m_y);
	}

	bool operator!=(Vec2 const& lhs, Vec2 const& rhs)
	{
		return (lhs.m_x != rhs.m_x || lhs.m_y != rhs.m_y);
	}

	Vec2 operator-(Vec2 const& other)
	{
		return Vec2(-other.m_x, -other.m_y);
	}

	Vec2 operator+(Vec2 const& lhs, Vec2 const& rhs)
	{
		return Vec2(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y);
	}

	Vec2 operator-(Vec2 const& lhs, Vec2 const& rhs)
	{
		return Vec2(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
	}

	Vec2 operator*(Vec2 const& lhs, Vec2 const& rhs)
	{
		return Vec2(lhs.m_x * rhs.m_x, lhs.m_y * rhs.m_y);
	}

	Vec2 operator*(Vec2 const& lhs, float scalar)
	{
		return Vec2(lhs.m_x * scalar, lhs.m_y * scalar);
	}

	Vec2 operator/(Vec2 const& lhs, Vec2 const& rhs)
	{
		return Vec2(lhs.m_x / rhs.m_x, lhs.m_y / rhs.m_y);
	}

	Vec2 operator/(Vec2 const& lhs, float scalar)
	{
		return Vec2(lhs.m_x / scalar, lhs.m_y / scalar);
	}

	Vec2& operator+=(Vec2& lhs, Vec2 const& rhs)
	{
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;

		return lhs;
	}

	Vec2& operator-=(Vec2& lhs, Vec2 const& rhs)
	{
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;

		return lhs;
	}

	Vec2& operator*=(Vec2& lhs, Vec2 const& rhs)
	{
		lhs.m_x *= rhs.m_x;
		lhs.m_y *= rhs.m_y;

		return lhs;
	}

	Vec2& operator/=(Vec2& lhs, Vec2 const& rhs)
	{
		lhs.m_x /= rhs.m_x;
		lhs.m_y /= rhs.m_y;

		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, Vec2 const& other)
	{
		return os << other.string();
	}

	std::istream& operator>>(std::istream& is, Vec2& output)
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