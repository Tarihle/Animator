#ifndef __LIBMATH__VECTOR__VECTOR3_H__
#define __LIBMATH__VECTOR__VECTOR3_H__

#include <iostream>
#include <string>

#include "LibMath/Angle/Radian.h"

namespace LibMath
{
class Vec2;
class Vec4;

class Vec3
{
  public:
	/* CONSTRUCTORS & DESTRUCTOR */

	/// <summary>Non-parameterized constructor.</summary>
	/// <returns>Vec3 filled with zeros.</returns>
	Vec3(void) = default;

	/// <summary>Mono-parameterized constructor.</summary>
	/// <param name="value">: Value to fill the vector with.</param>
	/// <returns>Vec3 filled with the given value.</returns>
	explicit Vec3(float value) : Vec3(value, value, value)
	{
	}

	/// <summary>Components constructor.</summary>
	/// <param name="x">: Component on the 'x' axis.</param>
	/// <param name="y">: Component on the 'y' axis.</param>
	/// <param name="z">: Component on the 'z' axis.</param>
	/// <returns>Vec3 with corresponding components.</returns>
	Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
	{
	}

	/// <summary>Copy constructor.</summary>
	/// <param name="other">: Vector to copy.</param>
	/// <returns>Copy of given vector.</returns>
	Vec3(Vec3 const& other) = default;

	/// <summary>Move constructor.</summary>
	/// <param name="other">: Vector to steal from.</param>
	/// <returns>New vector.</returns>
	Vec3(Vec3&&) = default;

	/// <summary>Destructor.</summary>
	~Vec3(void) = default;

	/* STATIC FUNCTIONS */

	/// <returns>Vector filled with zeros.</returns>
	static Vec3 zero(void);

	/// <returns>Vector filled with ones.</returns>
	static Vec3 one(void);

	/// <returns>Vector pointing up (positive y).</returns>
	static Vec3 up(void);

	/// <returns>Vector pointing down (negative y).</returns>
	static Vec3 down(void);

	/// <returns>Vector pointing left (negative x).</returns>
	static Vec3 left(void);

	/// <returns>Vector pointing right (positive x).</returns>
	static Vec3 right(void);

	/// <returns>Vector pointing frontwards (positive z).</returns>
	static Vec3 front(void);

	/// <returns>Vector pointing backwards (negative z).</returns>
	static Vec3 back(void);

	/// <summary>Calculates the dot product between 2 Vec3.</summary>
	/// <param name="u">: First Vec3.</param>
	/// <param name="v">: Second Vec3.</param>
	/// <returns>Result of the dot product.</returns>
	static float dot(Vec3 const& u, Vec3 const& v);

	/// <summary>Find a vector perpendicular to 2 vectors without using cross product.</summary>
	/// <param name="u">: First Vec3.</param>
	/// <param name="v">: Second Vec3.</param>
	/// <returns>Normal vector.</returns>
	static Vec3 alternativePerp(Vec3 const& u, Vec3 const& v);

	/* IN-CLASS OPERATORS */

	/// <summary>Copy assignment.</summary>
	/// <param name="other">: Vector to copy the data of.</param>
	/// <returns>Modified Vec3.</returns>
	Vec3& operator=(Vec3 const& other) = default;

	/// <summary>Move assignment.</summary>
	/// <param name="other">: Vector to steal the data from.</param>
	/// <returns>Modified Vec3.</returns>
	Vec3& operator=(Vec3&&) = default;

	/// <summary>Indexing components.</summary>
	/// <param name="index">: Index of the wanted parameter.</param>
	/// <returns>Corresponding component reference.</returns>
	float& operator[](int index);

	/// <summary>Indexing components of a const Vec3.</summary>
	/// <param name="index">: Index of the wanted parameter.</param>
	/// <returns>Corresponding component.</returns>
	float operator[](int index) const;

	/// <summary>Multiply all components by a scalar.</summary>
	/// <param name="scalar">: Scalar to multiply by.</param>
	/// <returns>Modified vector.</returns>
	Vec3& operator*=(float scalar);

	/// <summary>Divide all components by a scalar.</summary>
	/// <param name="scalar">: Scalar to divide by.</param>
	/// <returns>Modified vector.</returns>
	Vec3& operator/=(float scalar);

	/// <summary>Converts a Vec3 to Vec2.</summary>
	/// <returns>Vec2 (only x and y).</returns>
	operator Vec2(void) const;

	/// <summary>Converts a Vec3 to Vec4.</summary>
	/// <returns>Homogenized Vec4.</returns>
	operator Vec4(void) const;

	/*  CLASS FUNCTIONS */

	/// <summary>Angle between two Vec3.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Angle in radians.</returns>
	Radian angleFrom(Vec3 const& other) const;

	/// <summary>Oriented angle between two Vec3 based from an axis.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>oriented Angle in radians.</returns>
	Radian orientedAngleFrom(Vec3 const& other, Vec3 const& axisRef) const;

	/// <summary>Cross product between two Vec3.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Resultant Vec3.</returns>
	Vec3 cross(Vec3 const& other) const;

	/// <summary>Distance between two Vec3.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Distance in float form.</returns>
	float distanceFrom(Vec3 const& other) const;

	/// <summary>Squared distance between two Vec3.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Squared distance in float form.</returns>
	float distanceSquaredFrom(Vec3 const& other) const;

	/// <summary>Distance between two Vec3 on the X-Y plane.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Distance in float form.</returns>
	float distance2DFrom(Vec3 const& other) const;

	/// <summary>Squared distance between two Vec3 on the X-Y plane.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Squared distance in float form.</returns>
	float distance2DSquaredFrom(Vec3 const& other) const;

	/// <summary>Dot product between two Vec3.</summary>
	/// <param name="other">: Other Vec3 to calculate with.</param>
	/// <returns>Scalar in float form.</returns>
	float dot(Vec3 const& other) const;

	/// <summary>Size comparison with another Vec3.</summary>
	/// <param name="other">: Other Vec3 to compare from.</param>
	/// <returns>True if longer.</returns>
	bool isLongerThan(Vec3 const& other) const;

	/// <summary>Size comparison with another Vec3.</summary>
	/// <param name="other">: Other Vec3 to compare from.</param>
	/// <returns>True if shorter.</returns>
	bool isShorterThan(Vec3 const& other) const;

	/// <summary>Checking if this object is a unit vector.</summary>
	/// <returns>True if magnitude equals one.</returns>
	bool isUnitVector(void) const;

	/// <summary>Magnitude calculation.</summary>
	/// <returns>Magnitude in float form.</returns>
	float magnitude(void) const;

	/// <summary>Squared magnitude calculation.</summary>
	/// <returns>Squared magnitude in float form.</returns>
	float magnitudeSquared(void) const;

	/// <summary>Normalizing Vec3.</summary>
	/// <returns>Normalized vector.</returns>
	Vec3& normalize(void);

	/// <summary>Normalizing Vec3.</summary>
	/// <returns>New normalized vector.</returns>
	Vec3 normalizenew(void) const;

	/// <summary>Project on another Vec3.</summary>
	/// <param name="other">: Other Vec3 to project on.</param>
	/// <returns>Modified vector.</returns>
	Vec3& projectOnto(Vec3 const& other);

	/// <summary>Project on another Vec3.</summary>
	/// <param name="other">: Other Vec3 to reflect on.</param>
	/// <returns>Modified vector.</returns>
	Vec3& reflectOnto(Vec3 const&);

	/// <summary>Rotation with angles.</summary>
	/// <param name="z">: Z axis angle.</param>
	/// <param name="x">: X axis angle.</param>
	/// <param name="y">: Y axis angle.</param>
	/// <returns>Modified vector.</returns>
	Vec3& rotate(Radian z, Radian x, Radian y);

	/// <summary>Rotation of angle r around an axis.</summary>
	/// <param name="r">: angle of rotation.</param>
	/// <returns>Modified vector.</returns>
	Vec3& rotate(Radian r, Vec3 const&);

	// void			rotate(Quaternion const&); todo quaternion		// rotate this vector using a quaternion rotor

	/// <summary>Scaling by components.</summary>
	/// <param name="other">: Components to scale by.</param>
	/// <returns>Modified vector.</returns>
	Vec3& scale(Vec3 const& other);

	/// <summary>Translating by components.</summary>
	/// <param name="other">: Components to translate by.</param>
	/// <returns>Modified vector.</returns>
	Vec3& translate(Vec3 const&);

	/// <returns>Vector as a string.</returns>
	std::string string(void) const;

	/// <returns>Vector as a verbose string.</returns>
	std::string stringLong(void) const;

	/* Vec3's components */
	float m_z{ 0 }, m_y{ 0 }, m_x{ 0 };
};

/* OUT-OF-CLASS OPERATORS */

/// <summary>Comparison between two vectors component-wise.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>True if all components are equal.</returns>
bool operator==(Vec3 const& lhs, Vec3 const& rhs);

/// <summary>Comparison between two vectors component-wise.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>True if not all components are equal.</returns>
bool operator!=(Vec3 const& lhs, Vec3 const& rhs);

/// <summary>Inverts a vector's components.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <returns>New inverted vector.</returns>
Vec3 operator-(Vec3 const& lhs);

/// <summary>Adding two vectors (components) together.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>New result vector.</returns>
Vec3 operator+(Vec3 const&, Vec3 const&);

/// <summary>Substracting a vector (components) from another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>New result vector.</returns>
Vec3 operator-(Vec3 const&, Vec3 const&);

/// <summary>Multiply all components by a scalar.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="scalar">: Scalar to multiply by.</param>
/// <returns>New result vector.</returns>
Vec3 operator*(Vec3 const&, float scalar);

/// <summary>Multiply all components by a scalar.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="scalar">: Scalar to multiply by.</param>
/// <returns>New result vector.</returns>
Vec3 operator*(float, Vec3 const&);

/// <summary>Multiplying two vectors (components) together.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>New result vector.</returns>
Vec3 operator*(Vec3 const&, Vec3 const&);

/// <summary>Dividing a vector (components) by another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="scalar">: Scalar to divide by.</param>
/// <returns>New result vector.</returns>
Vec3 operator/(Vec3 const&, float scalar);

/// <summary>Dividing a vector (components) by another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>New result vector.</returns>
Vec3 operator/(Vec3 const&, Vec3 const&);

/// <summary>Adding a vector (components) to another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>Modified lhs vector.</returns>
Vec3& operator+=(Vec3&, Vec3 const&);

/// <summary>Substracting a vector (components) from another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>Modified lhs vector.</returns>
Vec3& operator-=(Vec3&, Vec3 const&);

/// <summary>Multiplying a vector (components) to another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>Modified lhs vector.</returns>
Vec3& operator*=(Vec3&, Vec3 const&);

/// <summary>Dividing a vector (components) by another.</summary>
/// <param name="lhs">: left hand side vector.</param>
/// <param name="rhs">: right hand side vector.</param>
/// <returns>Modified lhs vector.</returns>
Vec3& operator/=(Vec3&, Vec3 const&);

/// <summary>Outputing the string version of a vector.</summary>
std::ostream& operator<<(std::ostream&, Vec3 const&);

/// <summary>Inputing the string version of a vector..</summary>
std::istream& operator>>(std::istream&, Vec3&);
} // namespace LibMath

#endif // !__LIBMATH__VECTOR__VECTOR3_H__
