#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector/Vec2.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class T>
	struct Matrix<2, 2, T>
	{
		typedef LibMath::Vec2 _ColumnType;
		typedef LibMath::Vec2 _RowType;

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
		/// <returns>Mat2 filled with the given value.</returns>
		explicit Matrix(T v);

		/// <summary>Vector based constructor.</summary>
		/// <param name="row1">: First row vector.</param>
		/// <param name="row2">: Second row vector.</param>
		/// <returns>Matrix filled with the given vectors.</returns>
		Matrix(const _RowType& row1, const _RowType& row2);

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
		static Matrix<2, 2, T> Zero(void);

		/// <returns>Identity matrix.</returns>
		static Matrix<2, 2, T> Identity(void) requires (std::is_arithmetic_v<T>);



		/*  CLASS FUNCTIONS */

		/// <summary>Transforms current matrix to identity matrix.</summary>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& ToIdentity(void) requires (std::is_arithmetic_v<T>);

		/// <summary>Empties the matrix by filling it with empty objects.</summary>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& Empty(void);

		/// <returns>Transpose of the current matrix.</returns>
		Matrix<2, 2, T> GetTranspose(void) const;

		/// <summary>Changes the current matrix to its transpose.</summary>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& ToTranspose(void);

		/// <summary>Calculates the determinant of the current matrix.</summary>
		/// <returns>Determinant of the current matrix.</returns>
		T GetDeterminant(void) const;

		/// <summary>Calculates a minor of a matrix with a removed row and column.</summary>
		/// <param name="row">: Row to remove.</param>
		/// <param name="column">: Column to remove.</param>
		/// <returns>Resulting object.</returns>
		T GetMinor(int row, int column) const;



		/* IN-CLASS OPERATORS */

		/// <summary>Copy assignment.</summary>
		/// <param name="rhs">: Matrix to copy the data of.</param>
		/// <returns>Modified Matrix.</returns>
		Matrix<2, 2, T>& operator=(const Matrix<2, 2, T>&) = default;

		/// <summary>Move assignment.</summary>
		/// <param name="rhs">: Matrix to steal the data of.</param>
		/// <returns>Modified Matrix.</returns>
		Matrix<2, 2, T>& operator=(Matrix<2, 2, T>&&) = default;

		/// <summary>Comparison operator.</summary>
		/// <param name="rhs">: Matrix to compare with.</param>
		/// <returns>True if all values are the same, false if not.</returns>
		bool operator==(const Matrix<2, 2, T >& rhs) const requires(std::is_arithmetic_v<T>);

		/// <summary>Comparison operator.</summary>
		/// <param name="rhs">: Matrix to compare with.</param>
		/// <returns>True if at least one value is different, false if not.</returns>
		bool operator!=(const Matrix<2, 2, T>& rhs) const requires(std::is_arithmetic_v<T>);

		/// <summary>Indexing components.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component reference.</returns>
		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }

		/// <summary>Indexing components of a const Matrix.</summary>
		/// <param name="index">: Index of the wanted parameter.</param>
		/// <returns>Corresponding component.</returns>
		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }

		/*template <size_t _C, class _Other>
			requires std::is_convertible_v<_Other, Matrix<2, _C, _Type>>
		Matrix<2, _C, _Type> operator*(const _Other& rhs) const;*/

		/// <summary>Multiplies the current matrix with another.</summary>
		/// <typeparam name="_C">: Number of columns.</typeparam>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Resulting matrix.</returns>
		template <size_t _C>
		Matrix<2, _C, T> operator*(const Matrix<2, _C, T>& rhs) const;

		/// <summary>Multiplies the current matrix with another.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& operator*=(const Matrix<2, 2, T>& rhs);

		/// <summary>Multiplies the current matrix with a scalar.</summary>
		/// <param name="rhs">: Scalar to multiply by.</param>
		/// <returns>Resulting matrix.</returns>
		Matrix<2, 2, T> operator*(T rhs) const;

		/// <summary>Multiplies the current matrix with a scalar.</summary>
		/// <param name="rhs">: Scalar to multiply by.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& operator*=(T rhs);

		/// <summary>Adds another matrix to the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Resulting matrix.</returns>
		Matrix<2, 2, T> operator+(const Matrix<2, 2, T>& rhs) const;

		/// <summary>Adds another matrix to the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& operator+=(const Matrix<2, 2, T>& rhs);

		/// <summary>Substracts another matrix from the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Resulting matrix.</returns>
		Matrix<2, 2, T> operator-(const Matrix<2, 2, T>& rhs) const;

		/// <summary>Substracts another matrix from the current matrix.</summary>
		/// <param name="rhs">: Right hand side matrix.</param>
		/// <returns>Modified matrix.</returns>
		Matrix<2, 2, T>& operator-=(const Matrix<2, 2, T>& rhs);

	private:
		/* COMPONENTS */

		_ColumnType m_matrix[2];
	};

	/// <summary>Outputing the string version of a matrix.</summary>
	template <class T = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<2, 2, T>& matrix);

	using Mat2 = typename Matrix<2, 2, float>;
}

#include <LibMath/Matrix/Mat2x2.hpp>