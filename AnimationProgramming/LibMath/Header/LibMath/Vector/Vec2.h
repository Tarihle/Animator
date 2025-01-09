#ifndef __LIBMATH__VECTOR__VECTOR2_H__
#define __LIBMATH__VECTOR__VECTOR2_H__

#include <string>

#include "LibMath/Angle/Radian.h"

namespace LibMath
{
	class Vec3;
	class Vec4;

	class Vec2
	{
	public:


		/* CONSTRUCTORS & DESTRUCTOR */

		/// <summary>Non-parameterized constructor.</summary>
		/// <returns>Vec2 filled with zeros.</returns>
		Vec2(void) = default;

		/// <summary>Mono-parameterized constructor.</summary>
		/// <param name="value">: Value to fill the vector with.</param>
		/// <returns>Vec2 filled with the given value.</returns>
		explicit Vec2(float value) : Vec2(value, value) {}

		/// <summary>Components constructor.</summary>
		/// <param name="x">: Component on the 'x' axis.</param>
		/// <param name="y">: Component on the 'y' axis.</param>
		/// <returns>Vec2 with corresponding components.</returns>
		Vec2(float x, float y) : m_x(x), m_y(y) {}

		/// <summary>Copy constructor.</summary>
		/// <param name="other">: Vector to copy.</param>
		/// <returns>Copy of given vector.</returns>
		Vec2(Vec2 const&) = default;

		/// <summary>Move constructor.</summary>
		/// <param name="other">: Vector to steal from.</param>
		/// <returns>New vector.</returns>
		Vec2(Vec2&&) = default;

		/// <summary>Destructor.</summary>
		~Vec2(void) = default;



		/* STATIC FUNCTIONS */

		/// <returns>Vector filled with zeros.</returns>
		static Vec2	zero(void);

		/// <returns>Vector filled with ones.</returns>
		static Vec2	one(void);

		/// <returns>Vector pointing up (positive y).</returns>
		static Vec2	up(void);

		/// <returns>Vector pointing down (negative y).</returns>
		static Vec2	down(void);

		/// <returns>Vector pointing left (negative x).</returns>
		static Vec2	left(void);

		/// <returns>Vector pointing right (positive x).</returns>
		static Vec2	right(void);



		/* IN-CLASS OPERATORS */

		/// <summary>Copy assignment.</summary>
		/// <param name="other">: Vector to copy the data of.</param>
		/// <returns>Modified Vec2.</returns>
		Vec2&	operator=(Vec2 const&) = default;

		/// <summary>Move assignment.</summary>
		/// <param name="other">: Vector to steal the data from.</param>
		/// <returns>Modified Vec2.</returns>
		Vec2&	operator=(Vec2&&) = default;

		/// <summary>Indexing components.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component reference.</returns>
		float&	operator[](int);

		/// <summary>Indexing components of a const Vec2.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component.</returns>
		float	operator[](int) const;

		/// <summary>Multiply all components by a scalar.</summary>
		/// <param name="scalar">: Scalar to multiply by.</param>
		/// <returns>Modified vector.</returns>
		Vec2& operator*=(float scalar);

		/// <summary>Divide all components by a scalar.</summary>
		/// <param name="scalar">: Scalar to divide by.</param>
		/// <returns>Modified vector.</returns>
		Vec2& operator/=(float scalar);

		/// <summary>Converts a Vec2 to Vec3.</summary>
		/// <returns>Homogenized Vec4.</returns>
		operator Vec3(void) const;

		/// <summary>Converts a Vec2 to Vec4.</summary>
		/// <returns>Homogenized Vec4.</returns>
		operator Vec4(void) const;



		/*  CLASS FUNCTIONS */

		/// <summary>Angle between two Vec2.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Angle in radians.</returns>
		Radian	angleFrom(Vec2 const& other) const;

		/// <summary>Cross product between two Vec2.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Resultant Vec2.</returns>
		float	cross(Vec2 const& other) const;

		/// <summary>Distance between two Vec2.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Distance in float form.</returns>
		float	distanceFrom(Vec2 const& other) const;

		/// <summary>Squared distance between two Vec2.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Squared distance in float form.</returns>
		float	distanceSquaredFrom(Vec2 const& other) const;

		/// <summary>Distance between two Vec2 on the X-Y plane.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Distance in float form.</returns>
		float	distance2DFrom(Vec2 const& other) const;

		/// <summary>Squared distance between two Vec2 on the X-Y plane.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Squared distance in float form.</returns>
		float	distance2DSquaredFrom(Vec2 const& other) const;

		/// <summary>Dot product between two Vec2.</summary>
		/// <param name="other">: Other Vec2 to calculate with.</param>
		/// <returns>Scalar in float form.</returns>
		float	dot(Vec2 const& other) const;

		/// <summary>Size comparison with another Vec2.</summary>
		/// <param name="other">: Other Vec2 to compare from.</param>
		/// <returns>True if longer.</returns>
		bool	isLongerThan(Vec2 const& other) const;

		/// <summary>Size comparison with another Vec2.</summary>
		/// <param name="other">: Other Vec2 to compare from.</param>
		/// <returns>True if shorter.</returns>
		bool	isShorterThan(Vec2 const& other) const;

		/// <summary>Checking if this object is a unit vector.</summary>
		/// <returns>True if magnitude equals one.</returns>
		bool	isUnitVector(void) const;

		/// <summary>Magnitude calculation.</summary>
		/// <returns>Magnitude in float form.</returns>
		float	magnitude(void) const;

		/// <summary>Squared magnitude calculation.</summary>
		/// <returns>Squared magnitude in float form.</returns>
		float	magnitudeSquared(void) const;

		/// <summary>Normalizing Vec2.</summary>
		/// <returns>Normalized vector.</returns>
		Vec2&	normalize(void);

		/// <summary>Normalizing Vec2.</summary>
		/// <returns>New normalized vector.</returns>
		Vec2	normalizenew(void) const;

		/// <summary>Project on another Vec2.</summary>
		/// <param name="other">: Other Vec2 to project on.</param>
		/// <returns>Modified vector.</returns>
		Vec2&	projectOnto(Vec2 const& other);

		/// <summary>Project on another Vec2.</summary>
		/// <param name="other">: Other Vec2 to reflect on.</param>
		/// <returns>Modified vector.</returns>
		Vec2&	 reflectOnto(Vec2 const& other);

		/// <summary>Rotation with angles.</summary>
		/// <param name="x">: X axis angle.</param>
		/// <param name="y">: Y axis angle.</param>
		/// <returns>Modified vector.</returns>
		Vec2&	rotate(Radian x, Radian y);

		/// <summary>Rotation of angle r around an axis.</summary>
		/// <param name="r">: angle of rotation.</param>
		/// <returns>Modified vector.</returns>
		Vec2&	rotate(Radian, Vec2 const&);

		//void			rotate(Quaternion const&); todo quaternion		// rotate this vector using a quaternion rotor

		/// <summary>Scaling by components.</summary>
		/// <param name="other">: Components to scale by.</param>
		/// <returns>Modified vector.</returns>
		Vec2&	scale(Vec2 const&);

		/// <summary>Translating by components.</summary>
		/// <param name="other">: Components to translate by.</param>
		/// <returns>Modified vector.</returns>
		Vec2&	translate(Vec2 const&);

		/// <returns>Vector as a string.</returns>
		std::string	string(void) const;

		/// <returns>Vector as a verbose string.</returns>
		std::string	stringLong(void) const;		
		
		

		/* Vec2's components */
		float m_y{ 0 }, m_x{ 0 };
	};

	/* OUT-OF-CLASS OPERATORS */

	/// <summary>Comparison between two vectors component-wise.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>True if all components are equal.</returns>
	bool			operator==(Vec2 const&, Vec2 const&);

	/// <summary>Comparison between two vectors component-wise.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>True if not all components are equal.</returns>
	bool			operator!=(Vec2 const&, Vec2 const&);

	/// <summary>Inverts a vector's components.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <returns>New inverted vector.</returns>
	Vec2			operator-(Vec2 const&);

	/// <summary>Adding two vectors (components) together.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec2			operator+(Vec2 const&, Vec2 const&);

	/// <summary>Substracting a vector (components) from another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec2			operator-(Vec2 const&, Vec2 const&);

	/// <summary>Multiplying two vectors (components) together.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec2			operator*(Vec2 const&, Vec2 const&);

	/// <summary>Multiplying two vectors (components) together.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="scalar">: scalar to multiply by.</param>
	/// <returns>New result vector.</returns>
	Vec2			operator*(Vec2 const&, float);

	/// <summary>Dividing a vector (components) by another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>New result vector.</returns>
	Vec2			operator/(Vec2 const&, Vec2 const&);

	/// <summary>Dividing a vector (components) by another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="scalar">: scalar to divide by.</param>
	/// <returns>New result vector.</returns>
	Vec2			operator/(Vec2 const&, float);

	/// <summary>Adding a vector (components) to another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec2& operator+=(Vec2&, Vec2 const&);

	/// <summary>Substracting a vector (components) from another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec2& operator-=(Vec2&, Vec2 const&);

	/// <summary>Multiplying a vector (components) to another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec2& operator*=(Vec2&, Vec2 const&);

	/// <summary>Dividing a vector (components) by another.</summary>
	/// <param name="lhs">: left hand side vector.</param>
	/// <param name="rhs">: right hand side vector.</param>
	/// <returns>Modified lhs vector.</returns>
	Vec2& operator/=(Vec2&, Vec2 const&);

	/// <summary>Outputing the string version of a vector.</summary>
	std::ostream& operator<<(std::ostream&, Vec2 const&);

	/// <summary>Inputing the string version of a vector..</summary>
	std::istream& operator>>(std::istream&, Vec2&);
}

#endif // !__LIBMATH__VECTOR__VECTOR2_H__