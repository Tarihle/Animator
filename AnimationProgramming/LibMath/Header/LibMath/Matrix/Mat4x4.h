#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class T>
	struct Matrix<4, 4, T> 
	{
		typedef Vec4 _ColumnType;
		typedef Vec4 _RowType;

	public:


		/* CONSTRUCTORS & DESTRUCTOR */

		/// <summary>Non-parameterized constructor.</summary>
		/// <returns>Empty matrix.</returns>
		Matrix(void) = default;

		/// <summary>Copy constructor.</summary>
		/// <param name="other">: Matrix to copy.</param>
		/// <returns>Copy of given matrix.</returns>
		Matrix(const Matrix& other) = default;

		/// <summary>Move constructor.</summary>
		/// <param name="other">: Matrix to steal from.</param>
		/// <returns>New matrix.</returns>
		Matrix(Matrix&& other) = default;

		/// <summary>Mono-parameterized constructor.</summary>
		/// <param name="v">: Value to fill the matrix with.</param>
		/// <returns>Mat4 filled with the given value.</returns>
		explicit Matrix(T v);

		/// <summary>Vector based constructor.</summary>
		/// <param name="row1">: First row vector.</param>
		/// <param name="row2">: Second row vector.</param>
		/// <param name="row3">: Third row vector.</param>
		/// <param name="row4">: Fourth row vector.</param>
		/// <returns>Matrix filled with the given vectors.</returns>
		Matrix(const _RowType& row1, const _RowType& row2, const _RowType& row3, const _RowType& row4);

		/// <summary>Initializer list of values constructor.</summary>
		/// <param name="initList">: List of values to initialize the matrix with.</param>
		/// <returns>Matrix filled with the given value.</returns>
		Matrix(std::initializer_list<T> initList);

		/// <summary>Initializer list of vectors constructor.</summary>
		/// <param name="initList">: List of vectors to initialize the matrix with.</param>
		/// <returns>Matrix filled with the given vectors.</returns>
		Matrix(std::initializer_list<std::initializer_list<T>> initList);

		/// <summary>Destructor.</summary>
		~Matrix(void) = default;



		/* STATIC FUNCTIONS */

		/// <returns>Matrix filled with zeros.</returns>
		static Matrix<4, 4, T> Zero(void);

		/// <returns>Identity matrix.</returns>
		static Matrix<4, 4, T> Identity(void) requires (std::is_arithmetic_v<T>);

		/// <param name="translation">: Translation vector.</param>
		/// <returns>Translation matrix based on the given vector.</returns>
		static Matrix<4, 4, T> Translate(const Vec3& translation) requires(std::is_arithmetic_v<T>);

		/// <param name="rotation">: Rotation vector.</param>
		/// <returns>Rotation matrix based on the given vector.</returns>
		static Matrix<4, 4, T> Rotate(const Vec3& rotation) requires(std::is_arithmetic_v<T>);

		/// <param name="scale">: Scale vector.</param>
		/// <returns>Scale matrix based on the given vector.</returns>
		static Matrix<4, 4, T> Scale(const Vec3& scale) requires(std::is_arithmetic_v<T>);

		/// <summary>Calculates a perspective projection matrix with a given FoV, aspect, near and far distance.</summary>
		/// <param name="fov">: Vertical field of view.</param>
		/// <param name="aspect">: Aspect ratio of the width and the height of the "screen"</param>
		/// <param name="near">: Near distance.</param>
		/// <param name="far">: Far distance.</param>
		/// <returns>Perspective projection matrix</returns>
		static Matrix<4, 4, T> Perspective(T fov, T aspect, T near, T far) requires(std::is_arithmetic_v<T>);

		/// <summary>Calculates an orthographic projection matrix with given boundaries.</summary>
		/// <param name="left">: Left border.</param>
		/// <param name="right">: Right border.</param>
		/// <param name="bottom">: Bottom border.</param>
		/// <param name="top">: Top border.</param>
		/// <returns>Orthographic projection matrix</returns>
		static Matrix<4, 4, T> Ortho(T left, T right, T bottom, T top) requires(std::is_arithmetic_v<T>);

		/// <summary>Calculates an orthographic projection matrix with given boundaries.</summary>
		/// <param name="left">: Left border.</param>
		/// <param name="right">: Right border.</param>
		/// <param name="bottom">: Bottom border.</param>
		/// <param name="top">: Top border.</param>
		/// <param name="near">: Near border.</param>
		/// <param name="far">: Far border.</param>
		/// <returns>Orthographic projection matrix</returns>
		static Matrix<4, 4, T> Ortho(T left, T right, T bottom, T top, T near, T far) requires(std::is_arithmetic_v<T>);

		/// <summary>Calculates a view matrix based on positions and vectors of the observer and target.<para />
		/// This view matrix is Left-Handed.</summary>
		/// <param name="eye">: Position of the observer.</param>
		/// <param name="center">: Position of the target.</param>
		/// <param name="up">: Up vector of the observer.</param>
		/// <returns>View matrix.</returns>
		static Matrix<4, 4, T> LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);



		/*  CLASS FUNCTIONS */

		/// <summary>Transforms current matrix to identity matrix.</summary>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& ToIdentity(void) requires (std::is_arithmetic_v<T>);

		/// <summary>Empties the matrix by filling it with empty objects.</summary>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& Empty(void);

		/// <returns>Transpose of the current matrix.</returns>
		Matrix<4, 4, T> GetTranspose(void) const;

		/// <summary>Changes the current matrix to its transpose.</summary>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& ToTranspose(void);

		/// <summary>Calculates the determinant of the current matrix.</summary>
		/// <returns>Determinant of the current matrix.</returns>
		T GetDeterminant(void) const;

		/// <summary>Calculates a minor of a matrix with a removed row and column.</summary>
		/// <param name="row">: Row to remove.</param>
		/// <param name="column">: Column to remove.</param>
		/// <returns>3x3 equivalent matrix.</returns>
		Matrix<3, 3, T> GetMinor(size_t row, size_t column) const;

		/// <summary>Calculates the determinant of all the minor matrices of the current matrix.</summary>
		/// <returns>Minors determinant matrix.</returns>
		Matrix<4, 4, T> GetMinorsDeterminant(void) const;

		/// <summary>Calculates the cofactors of the current matrix.<para />
		/// The cofactor matrix is the MinorsDeterminant matrix multiplied by 1 or -1 depending on the row and column.</summary>
		/// <returns>Cofactors determinant matrix</returns>
		Matrix<4, 4, T> GetCofactors(void) const;

		/// <summary>Calculates the inverse of the current matrix.</summary>
		/// <returns>Inverse matrix.</returns>
		Matrix<4, 4, T> GetInverse(void) const;



		/* IN-CLASS OPERATORS */

		/// <summary>Copy assignment.</summary>
		/// <param name="rhs">: Matrix to copy the data of.</param>
		/// <returns>Modified Matrix.</returns>
		Matrix<4, 4, T>& operator=(const Matrix<4, 4, T>& rhs) = default;

		/// <summary>Move assignment.</summary>
		/// <param name="rhs">: Matrix to steal the data of.</param>
		/// <returns>Modified Matrix.</returns>
		Matrix<4, 4, T>& operator=(Matrix<4, 4, T>&& rhs) = default;

		/// <summary>Comparison operator.</summary>
		/// <param name="rhs">: Matrix to compare with.</param>
		/// <returns>True if all values are the same, false if not.</returns>
		bool operator==(const Matrix<4, 4, T>& rhs) const requires(std::is_arithmetic_v<T>);

		/// <summary>Comparison operator.</summary>
		/// <param name="rhs">: Matrix to compare with.</param>
		/// <returns>True if at least one value is different, false if not.</returns>
		bool operator!=(const Matrix<4, 4, T>& rhs) const requires(std::is_arithmetic_v<T>);

		/// <summary>Indexing components.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component reference.</returns>
		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }

		/// <summary>Indexing components of a const Matrix.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component.</returns>
		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }

		/*template <size_t _C, class _Other>
		Matrix<4, _C, T> operator*(const _Other& rhs) const;*/

		/// <summary>Multiplies the current matrix with another.</summary>
		/// <typeparam name="_C">: Number of columns.</typeparam>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Resulting matrix.</returns>
		template <size_t _C>
		Matrix<4, _C, T> operator*(const Matrix<4, _C, T>& rhs) const;

		/// <summary>Multiplies the current matrix with another.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& operator*=(const Matrix<4, 4, T>& rhs);

		/// <summary>Multiplies the current matrix with a scalar.</summary>
		/// <param name="rhs">: Scalar to multiply by.</param>
		/// <returns>Resulting matrix.</returns>
		Matrix<4, 4, T> operator*(T rhs) const;

		/// <summary>Multiplies the current matrix with a scalar.</summary>
		/// <param name="rhs">: Scalar to multiply by.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& operator*=(T rhs);

		/// <summary>Adds another matrix to the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Resulting matrix.</returns>
		Matrix<4, 4, T> operator+(const Matrix<4, 4, T>& rhs) const;

		/// <summary>Adds another matrix to the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& operator+=(const Matrix<4, 4, T>& rhs);

		/// <summary>Substracts another matrix from the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Resulting matrix.</returns>
		Matrix<4, 4, T> operator-(const Matrix<4, 4, T>& rhs) const;

		/// <summary>Substracts another matrix from the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<4, 4, T>& operator-=(const Matrix<4, 4, T>& rhs);

	private:
		/* COMPONENTS */

		_ColumnType m_matrix[4];
	};

	/* OUT-OF-CLASS OPERATORS */

	/// <summary>Multiplies a Vec4 with a Mat4.</summary>
	/// <param name="vec">: Vec4.</param>
	/// <param name="matrix">: Mat4.</param>
	/// <returns>Resulting Vec4.</returns>
	template <class T>
	Vec4 operator*(const Vec4& vec, const Matrix<4, 4, T>& matrix);

	/// <summary>Outputing the string version of a matrix.</summary>
	template <class T = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<4, 4, T>& matrix);

	using Mat4 = typename Matrix<4, 4, float>;
}

#include <LibMath/Matrix/Mat4x4.hpp>