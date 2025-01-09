#ifndef __LIBMATH__QUATERNION_H__
#define __LIBMATH__QUATERNION_H__

#include "LibMath/Vector/Vec4.h"
#include <LibMath/Matrix/Mat4x4.h>

namespace LibMath
{
class Quaternion
{
  public:
	/* CONSTRUCTORS & DESTRUCTOR */

	/// <summary>Non-parameterized constructor.</summary>
	/// <returns>Quaternion filled with zeros.</returns>
	Quaternion(void) = default;

	/// <summary>Mono-parameterized constructor.</summary>
	/// <param name="value">: Value to fill the quaternion with.</param>
	/// <returns>Quaternion filled with the given value.</returns>
	explicit Quaternion(float value) : Quaternion(value, value, value, value)
	{
	}

	/// <summary>Components constructor.</summary>
	/// <param name="x">: Component of the real part.</param>
	/// <param name="y">: Component of the 'i' part.</param>
	/// <param name="z">: Component of the 'j' part.</param>
	/// <param name="w">: Component of the 'k' part.</param>
	/// <returns>Quaternion with corresponding components.</returns>
	Quaternion(float a, float b, float c, float d) : m_a(a), m_b(b), m_c(c), m_d(d)
	{
	}

	/// <summary>Copy constructor.</summary>
	/// <param name="other">: Quaternion to copy.</param>
	/// <returns>Copy of given quaternion.</returns>
	Quaternion(Quaternion const& other) = default;

	/// <summary>Move constructor.</summary>
	/// <param name="other">: Quaternion to steal from.</param>
	/// <returns>New quaternion.</returns>
	Quaternion(Quaternion&& other) = default;

	/// <summary>Destructor.</summary>
	~Quaternion(void) = default;

	/* IN-CLASS OPERATORS */

	/// <summary>Copy assignment.</summary>
	/// <param name="other">: Quaternion to copy the data of.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator=(Quaternion const& other) = default;

	/// <summary>Move assignment.</summary>
	/// <param name="other">: Quaternion to steal the data from.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator=(Quaternion&& other) = default;

	/// <summary>Indexing components.</summary>
	/// <param name="index">: Index of the wanted parameter.</param>
	/// <returns>Corresponding component reference.</returns>
	float& operator[](int index);

	/// <summary>Indexing components of a const Quaternion.</summary>
	/// <param name="index">: Index of the wanted parameter.</param>
	/// <returns>Corresponding component.</returns>
	float operator[](int index) const;

	/// <summary>Adds another quaternion to this.</summary>
	/// <param name="rhs">: Quaternion to add.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator+=(Quaternion const& rhs);

	/// <summary>Substracts a quaternion from this.</summary>
	/// <param name="rhs">: Quaternion to substract from.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator-=(Quaternion const& rhs);

	/// <summary>Multiplies all components by a scalar.</summary>
	/// <param name="scalar">: Scalar to multiply by.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator*=(float scalar);

	/// <summary>Multiplies this by another quaternion.</summary>
	/// <param name="rhs">: Quaternion to multiply by.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator*=(Quaternion const& rhs);

	/// <summary>Divides all components by a scalar.</summary>
	/// <param name="scalar">: Scalar to divide by.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator/=(float scalar);

	/// <summary>Divides this by another quaternion.</summary>
	/// <param name="rhs">: Quaternion to divide by.</param>
	/// <returns>Modified quaternion.</returns>
	Quaternion& operator/=(Quaternion const& rhs);

	/// <summary>Converts a Quaternion to a Mat4.</summary>
	/// <returns>Quaternion in a 4x4 matrix form.</returns>
	operator Mat4(void) const;

	/*  CLASS FUNCTIONS */
	/// <summary>Magnitude calculation.</summary>
	/// <returns>Magnitude in float form.</returns>
	float magnitude(void) const;

	/// <summary>Squared magnitude calculation.</summary>
	/// <returns>Squared magnitude in float form.</returns>
	float magnitudeSquared(void) const;

	/// <summary>Converts this to its conjugate.</summary>
	/// <returns>Modified quaternion.</returns>
	Quaternion& toConjugate(void);

	/// <summary>Checks if this object is a unit quaternion.</summary>
	/// <returns>True if magnitude equals one.</returns>
	bool isUnitQuaternion(void) const;

	/// <summary>Normalizes this.</summary>
	/// <returns>Normalized quaternion.</returns>
	Quaternion& toUnitQuaternion(void);

	/// <summary>Returns the imaginary part of this.</summary>
	/// <returns>Vec3 part of the quaternion.</returns>
	Vec3 getVecPart(void) const;

	/* Quaternion's components */
	float m_a{ 0.f }, m_b{ 0.f }, m_c{ 0.f }, m_d{ 0.f };
};

/* OUT-OF-CLASS OPERATORS */

/// <summary>Adds 2 quaternions.</summary>
/// <param name="lhs">: Left hand quaternion of the operation.</param>
/// <param name="rhs">: Right hand quaternion of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator+(Quaternion const& lhs, Quaternion const& rhs);

/// <summary>Substracts a quaternion from another.</summary>
/// <param name="lhs">: Left hand quaternion of the operation.</param>
/// <param name="rhs">: Right hand quaternion of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator-(Quaternion const& lhs, Quaternion const& rhs);

/// <summary>Multiplies a quaternion by a scalar.</summary>
/// <param name="lhs">: Quaternion of the operation.</param>
/// <param name="scalar">: Scalar of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator*(Quaternion const& lhs, float scalar);

/// <summary>Multiplies a quaternion by a scalar.</summary>
/// <param name="scalar">: Scalar of the operation.</param>
/// <param name="rhs">: Quaternion of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator*(float scalar, Quaternion const& rhs);

/// <summary>Multiplies 2 quaternions.</summary>
/// <param name="lhs">: Left hand quaternion of the operation.</param>
/// <param name="rhs">: Right hand quaternion of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs);

/// <summary>Divides a quaternion by a scalar.</summary>
/// <param name="lhs">: Quaternion of the operation.</param>
/// <param name="scalar">: Scalar of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator/(Quaternion const& lhs, float scalar);

/// <summary>Divides a quaternion by a scalar.</summary>
/// <param name="scalar">: Scalar of the operation.</param>
/// <param name="rhs">: Quaternion of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator/(float scalar, Quaternion const& rhs);

/// <summary>Divides a quaternion by another.</summary>
/// <param name="lhs">: Left hand quaternion of the operation.</param>
/// <param name="rhs">: Right hand quaternion of the operation.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion operator/(Quaternion const& lhs, Quaternion const& rhs);

/* OUT-OF-CLASS FUNCTIONS */

/// <summary>Calculates the conjugate of a quaternion.</summary>
/// <param name="quat">: Quaternion to get the conjugate of.</param>
/// <returns>Conjugate of the given quaternion.</returns>
Quaternion conjugate(Quaternion const& quat);

/// <summary>Normalizes a quaternion.</summary>
/// <param name="quat">: Quaternion to normalize.</param>
/// <returns>Unit version of the given quaternion.</returns>
Quaternion normalize(Quaternion const& quat);

/// <summary>Spherical interpolation between 2 quaternions.</summary>
/// <param name="q">: First quaternion.</param>
/// <param name="r">: Second quaternion.</param>
/// <param name="t">: Decimal representation of a percentage.</param>
/// <returns>Resulting quaternion.</returns>
Quaternion slerp(Quaternion const& q, Quaternion const& r, float t);

/// <summary>Rotates a point about an axis.</summary>
/// <param name="rot">: "Rotation" quaternion.</param>
/// <param name="point">: Point to rotate.</param>
/// <returns>Resulting point in Vec4 form.</returns>
Vec4 rotatePoint(Quaternion const& rot, Vec4 const& point);

/// <summary>Converts a Quaternion to a Mat4.</summary>
/// <param name="quat">: Quaternion to convert.</param>
/// <returns>Quaternion in a 4x4 matrix form.</returns>
Mat4 toMat4(Quaternion const& quat);

/// <summary>Converts a Quaternion to a rotation Mat4.</summary>
/// <param name="quat">: Quaternion to convert.</param>
/// <returns>Rotation 4x4 matrix.</returns>
Mat4 toRotationMat4(Quaternion const& quat);
} // namespace LibMath

#endif // !__LIBMATH__QUATERNION_H__
