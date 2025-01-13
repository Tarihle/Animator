#ifndef __LIBMATH__VECTOR__VECTOR4_H__
#define __LIBMATH__VECTOR__VECTOR4_H__

#include <iostream>
#include <string>

#include "LibMath/Angle/Radian.h"

#include "LibMath/Vector/Vec2.h"
#include "LibMath/Vector/Vec3.h"

namespace LibMath
{
class Quaternion;

	class Vec4
	{
	public:


		/* CONSTRUCTORS & DESTRUCTOR */

		/// <summary>Non-parameterized constructor.</summary>
		/// <returns>Vec4 filled with zeros.</returns>
		Vec4(void) = default;

		/// <summary>Mono-parameterized constructor.</summary>
		/// <param name="value">: Value to fill the vector with.</param>
		/// <returns>Vec4 filled with the given value.</returns>
		explicit Vec4(float value) : Vec4(value, value, value, value) {}

		/// <summary>Components constructor.</summary>
		/// <param name="x">: Component on the 'x' axis.</param>
		/// <param name="y">: Component on the 'y' axis.</param>
		/// <param name="z">: Component on the 'z' axis.</param>
		/// <param name="w">: Component for homogeneous coordinates.</param>
		/// <returns>Vec4 with corresponding components.</returns>
		Vec4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}

		/// <summary>Copy constructor.</summary>
		/// <param name="other">: Vector to copy.</param>
		/// <returns>Copy of given vector.</returns>
		Vec4(Vec4 const&) = default;

		/// <summary>Move constructor.</summary>
		/// <param name="other">: Vector to steal from.</param>
		/// <returns>New vector.</returns>
		Vec4(Vec4&&) = default;

		/// <summary>Destructor.</summary>
		~Vec4(void) = default;



		/* STATIC FUNCTIONS */

		/// <returns>Vector filled with zeros.</returns>
		static Vec4	zero(void);

		/// <returns>Vector filled with ones.</returns>
		static Vec4	one(void);



		/*  CLASS FUNCTIONS */

		/// <summary>Angle between two Vec4.</summary>
		/// <param name="other">: Other Vec4 to calculate with.</param>
		/// <returns>Angle in radians.</returns>
		Radian			angleFrom(Vec4 const&) const;

		/// <summary>Cross product between two Vec4.</summary>
		/// <param name="other">: Other Vec4 to calculate with.</param>
		/// <returns>Resultant Vec4.</returns>
		float			distanceFrom(Vec4 const&) const;

		/// <summary>Distance between two Vec4.</summary>
		/// <param name="other">: Other Vec4 to calculate with.</param>
		/// <returns>Distance in float form.</returns>
		float			distanceSquaredFrom(Vec4 const&) const;

		/// <summary>Distance between two Vec4 on the X-Y plane.</summary>
		/// <param name="other">: Other Vec4 to calculate with.</param>
		/// <returns>Distance in float form.</returns>
		float			distance2DFrom(Vec4 const&) const;

		/// <summary>Squared distance between two Vec4 on the X-Y plane.</summary>
		/// <param name="other">: Other Vec4 to calculate with.</param>
		/// <returns>Squared distance in float form.</returns>
		float			distance2DSquaredFrom(Vec4 const&) const;

		/// <summary>Dot product between two Vec4.</summary>
		/// <param name="other">: Other Vec4 to calculate with.</param>
		/// <returns>Scalar in float form.</returns>
		float			dot(Vec4 const&) const;

		/// <summary>Size comparison with another Vec4.</summary>
		/// <param name="other">: Other Vec4 to compare from.</param>
		/// <returns>True if longer.</returns>
		bool			isLongerThan(Vec4 const&) const;

		/// <summary>Size comparison with another Vec4.</summary>
		/// <param name="other">: Other Vec4 to compare from.</param>
		/// <returns>True if shorter.</returns>
		bool			isShorterThan(Vec4 const&) const;

		/// <summary>Checking if this object is a unit vector.</summary>
		/// <returns>True if magnitude equals one.</returns>
		bool			isUnitVector(void) const;

		/// <summary>Magnitude calculation.</summary>
		/// <returns>Magnitude in float form.</returns>
		float			magnitude(void) const;

		/// <summary>Squared magnitude calculation.</summary>
		/// <returns>Squared magnitude in float form.</returns>
		float			magnitudeSquared(void) const;

		/// <summary>Normalizing Vec4.</summary>
		/// <returns>Normalized vector.</returns>
		Vec4& normalize(void);

		/// <summary>Normalizing Vec4.</summary>
		/// <returns>New normalized vector.</returns>
		Vec4 normalizenew(void) const;

		/// <summary>Project on another Vec4.</summary>
		/// <param name="other">: Other Vec4 to project on.</param>
		/// <returns>Modified vector.</returns>
		Vec4& projectOnto(Vec4 const&);

		/// <summary>Project on another Vec4.</summary>
		/// <param name="other">: Other Vec4 to reflect on.</param>
		/// <returns>Modified vector.</returns>
		Vec4& reflectOnto(Vec4 const&);

		/// <summary>Scaling by components.</summary>
		/// <param name="other">: Components to scale by.</param>
		/// <returns>Modified vector.</returns>
		Vec4& scale(Vec4 const&);

		/// <summary>Translating by components.</summary>
		/// <param name="other">: Components to translate by.</param>
		/// <returns>Modified vector.</returns>
		Vec4& translate(Vec4 const&);

		/// <returns>Vector as a string.</returns>
		std::string		string(void) const;

		/// <returns>Vector as a verbose string.</returns>
		std::string stringLong(void) const;

		/// <summary>Converts a Vec4 to quaternion.</summary>
		/// <returns>New quaternion.</returns>
		Quaternion toQuaternion(void) const;



		/* IN-CLASS OPERATORS */

		/// <summary>Copy assignment.</summary>
		/// <param name="other">: Vector to copy the data of.</param>
		/// <returns>Modified Vec4.</returns>
		Vec4&	operator=(Vec4 const&) = default;

		/// <summary>Move assignment.</summary>
		/// <param name="other">: Vector to steal the data from.</param>
		/// <returns>Modified Vec4.</returns>
		Vec4&	operator=(Vec4&&) = default;

		/// <summary>Indexing components.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component reference.</returns>
		float&	operator[](int);

		/// <summary>Indexing components of a const Vec4.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component.</returns>
		float	operator[](int) const;

		/// <summary>Multiplies all components by a scalar.</summary>
		/// <param name="scalar">: Scalar to multiply by.</param>
		/// <returns>Modified vector.</returns>
		Vec4&	operator*=(float scalar);

		/// <summary>Divides all components by a scalar.</summary>
		/// <param name="scalar">: Scalar to divide by.</param>
		/// <returns>Modified vector.</returns>
		Vec4&	operator/=(float scalar);

		/// <summary>Converts a Vec4 to Vec2.</summary>
		/// <returns>New Vec2.</returns>
		operator Vec2(void) const;

		/// <summary>Converts a Vec4 to Vec3.</summary>
		/// <returns>New Vec3.</returns>
		operator Vec3(void) const;



		/* COMPONENTS */

		//float m_w{ 0 }, m_x{ 0 }, m_y{ 0 }, m_z{ 0 };
		float m_x{ 0 }, m_y{ 0 }, m_z{ 0 }, m_w{ 0 };
		//float m_w{ 0 }, m_z{ 0 }, m_y{ 0 }, m_x{ 0 };
	};

	/* OUT-OF-CLASS OPERATORS */

	/// <summary>Comparison between two vectors component-wise.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>True if all components are equal.</returns>
	bool			operator==(Vec4 const&, Vec4 const&);

	/// <summary>Comparison between two vectors component-wise.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>True if not all components are equal.</returns>
	bool			operator!=(Vec4 const&, Vec4 const&);

	/// <summary>Inverts a vector's components.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <returns>New inverted vector.</returns>
	Vec4			operator-(Vec4 const&);

	/// <summary>Adding two vectors (components) together.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec4			operator+(Vec4 const&, Vec4 const&);

	/// <summary>Substracting a vector (components) from another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec4			operator-(Vec4 const&, Vec4 const&);

	/// <summary>Multiplying two vectors (components) together.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec4			operator*(Vec4 const&, Vec4 const&);

	/// <summary>Multiplying two vectors (components) together.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="scalar">: scalar to multiply by.</param>
	/// <returns>New result vector.</returns>
	Vec4			operator*(Vec4 const&, float);

	/// <summary>Dividing a vector (components) by another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec4			operator/(Vec4 const&, Vec4 const&);

	/// <summary>Dividing a vector (components) by another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="scalar">: scalar to divide by.</param>
	/// <returns>New result vector.</returns>
	Vec4			operator/(Vec4 const&, float);

	/// <summary>Adding a vector (components) to another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec4& operator+=(Vec4&, Vec4 const&);

	/// <summary>Substracting a vector (components) from another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec4& operator-=(Vec4&, Vec4 const&);

	/// <summary>Multiplying a vector (components) to another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec4& operator*=(Vec4&, Vec4 const&);

	/// <summary>Dividing a vector (components) by another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec4& operator/=(Vec4&, Vec4 const&);

	/// <summary>Outputing the string version of a vector.</summary>
	std::ostream& operator<<(std::ostream&, Vec4 const&);

	/// <summary>Inputing the string version of a vector.</summary>
	std::istream& operator>>(std::istream&, Vec4&);
}

#ifdef __LIBMATH__MATRIX__MATRIX4_H__
#include "Matrix4Vector4Operation.h"
#endif // __LIBMATH__MATRIX__MATRIX4_H__

#endif // !__LIBMATH__VECTOR__VECTOR4_H__
