#pragma once

#include <LibMath/Matrix/Mat2x2.h>
#include <LibMath/Matrix/Mat3x3.h>

namespace LibMath
{
	template<class T>
	Matrix<3, 3, T>::Matrix(T v)
	{
		for (int index = 0; index < 3; ++index)
			for (int jindex = 0; jindex < 3; ++jindex)
				if (index == jindex) (*this)[index][jindex] = v;
				else (*this)[index][jindex] = T(0);
	}

	template<class T>
	Matrix<3, 3, T>::Matrix(const _RowType& a, const _RowType& b, const _RowType& c)
	{
		(*this)[0] = a;
		(*this)[1] = b;
		(*this)[2] = c;
	}
	
	template<class T>
	Matrix<3, 3, T>::Matrix(std::initializer_list<T> initList)
	{
		if (initList.size() != 3 * 3) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		int index = 0;
		for (auto& element : initList)
		{
			for (int jindex = 0; jindex < 3; ++jindex)
				this->m_matrix[index][jindex] = std::move(element);

			++index;
		}
	}

	template<class T>
	Matrix<3, 3, T>::Matrix(std::initializer_list<std::initializer_list<T>> initList)
	{
		if (initList.size() != 3 || (initList.begin()->size() != 3)) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		int index = 0;
		for (auto& row : initList)
		{
			if (row.size() != 3)
			{
				throw std::invalid_argument("Invalid initializer list dimensions");
			}

			int jindex = 0;
			for (auto& element : row)
			{
				this->m_matrix[index][jindex++] = std::move(element);
			}

			++index;
		}
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::Zero(void)
	{
		Matrix<3, 3, T> matrix;

		for (int index = 0; index < 3; ++index)
			for (int jindex = 0; jindex < 3; ++jindex)
				matrix[index][jindex] = T();

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::Identity(void) requires (std::is_arithmetic_v<T>)
	{
		Matrix<3, 3, T> matrix;

		for (int index = 0; index < 3; ++index)
			for (int jindex = 0; jindex < 3; ++jindex)
				matrix[index][jindex] = std::move((index == jindex) ? T(1) : T());

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::Translate(const Vec2& other) requires (std::is_arithmetic_v<T>)
	{
		Matrix<3, 3, T> matrix = Matrix<3, 3, T>::Identity();
		matrix[0][2] = other[0];
		matrix[1][2] = other[1];

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::Rotate(const Vec2& other) requires (std::is_arithmetic_v<T>)
	{
		Matrix<3, 3, T> rotate = Matrix<3, 3, T>::Identity();
		Matrix<3, 3, T> matrix = Matrix<3, 3, T>::Identity();

		matrix[1][1] = std::cosf(other[0]);
		matrix[2][2] = std::cosf(other[0]);

		matrix[2][1] = std::sinf(other[0]);
		matrix[1][2] = -std::sinf(other[0]);

		rotate *= matrix;

		matrix.ToIdentity();

		matrix[0][0] = std::cosf(other[1]);
		matrix[2][2] = std::cosf(other[1]);

		matrix[0][2] = -std::sinf(other[1]);
		matrix[2][0] = std::sinf(other[1]);

		rotate *= matrix;
		return rotate;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::Scale(const Vec2& other) requires (std::is_arithmetic_v<T>)
	{
		Matrix<3, 3, T> matrix = Matrix<3, 3, T>::Identity();
		matrix[0][0] = other[0];
		matrix[2][2] = other[1];

		return matrix;
	}

	template<class T>
	bool Matrix<3, 3, T>::operator==(const Matrix<3, 3, T>& rhs) const requires(std::is_arithmetic_v<T>)
	{
		return this->m_matrix[0] == rhs.m_matrix[0]
			&& this->m_matrix[1] == rhs.m_matrix[1]
			&& this->m_matrix[2] == rhs.m_matrix[2];
	}

	template<class T>
	bool Matrix<3, 3, T>::operator!=(const Matrix<3, 3, T>& rhs) const requires(std::is_arithmetic_v<T>)
	{
		return this->m_matrix[0] != rhs.m_matrix[0]
			|| this->m_matrix[1] != rhs.m_matrix[1]
			|| this->m_matrix[2] != rhs.m_matrix[2];
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::ToIdentity(void)
		requires (std::is_arithmetic_v<T>)
	{
		for (int index = 0; index < 3; ++index)
			for (int jindex = 0; jindex < 3; ++jindex)
				(*this)[index][jindex] = std::move((index == jindex) ? T(1) : T());

		return *this;
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::Empty(void)
	{
		for (int index = 0; index < 3; ++index)
			for (int jindex = 0; jindex < 3; ++jindex)
				(*this)[index][jindex] = std::move(T());

		return *this;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::GetTranspose(void) const
	{
		Matrix<3, 3, T> matrix;

		for (int index = 0; index < 3; ++index)
			for (int jindex = 0; jindex < 3; ++jindex)
				matrix[jindex][index] = (*this)[index][jindex];

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::ToTranspose(void)
	{
		*this = std::move(this->GetTranspose());
		return *this;
	}

	template<class T>
	T Matrix<3, 3, T>::GetDeterminant(void) const
	{
		return (
			+((*this)[0][0] * (*this)[1][1] * (*this)[2][2])
			+ ((*this)[0][1] * (*this)[1][2] * (*this)[2][0])
			+ ((*this)[0][2] * (*this)[1][0] * (*this)[2][1])
			- ((*this)[0][0] * (*this)[1][2] * (*this)[2][1])
			- ((*this)[0][1] * (*this)[1][0] * (*this)[2][2])
			- ((*this)[0][2] * (*this)[1][1] * (*this)[2][0])
		);
	}

	template<class T>
	Matrix<2, 2, T> Matrix<3, 3, T>::GetMinor(int row, int column) const
	{
		Matrix<2, 2, T> matrix;

		int zindex = 0;
		for (int index = 0; index < 3; ++index)
		{
			int kindex = 0;
			for (int jindex = 0; jindex < 3; ++jindex)
			{
				if (index == row || jindex == column) continue;

				matrix[zindex][kindex] = (*this)[index][jindex];
				++kindex;
			}

			if (index != row) ++zindex;
		}

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::GetMinorsDeterminant(void) const
	{
		Matrix<3, 3, T> matrix;

		for (int index = 0; index < 3; ++index)
		{
			for (int jindex = 0; jindex < 3; ++jindex)
			{
				matrix[index][jindex] = this->GetMinor(index, jindex).GetDeterminant();
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::GetCofactors(void) const
	{
		Matrix<3, 3, T> matrix = std::move(this->GetMinorsDeterminant());

		for (int index = 0; index < 3; ++index)
		{
			for (int jindex = 0; jindex < 3; ++jindex)
			{
				matrix[index][jindex] *= ((index + jindex) % 2 > 0 ? -1 : 1);
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::GetInverse(void) const
	{
		Matrix<3, 3, T> matrix = this->GetCofactors().ToTranspose();
		matrix *= (1 / this->GetDeterminant());

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::operator*(T rhs) const
	{
		Matrix<3, 3, T> matrix = *this;

		for (int index = 0; index < 3; ++index)
			matrix[index] *= rhs;

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::operator+(const Matrix<3, 3, T>& rhs) const
	{
		Matrix<3, 3, T> matrix = *this;

		for (int index = 0; index < 3; ++index)
			matrix[index] += rhs[index];

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::operator+=(const Matrix<3, 3, T>& rhs)
	{
		*this = std::move(this->operator+(rhs));
		return *this;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<3, 3, T>::operator-(const Matrix<3, 3, T>& rhs) const
	{
		Matrix<3, 3, T> matrix = *this;

		for (size_t index = 0; index < 3; ++index)
			matrix[index] -= rhs[index];

		return matrix;
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::operator-=(const Matrix<3, 3, T>& rhs)
	{
		*this = std::move(this->operator-(rhs));
		return *this;
	}

	template<class T>
	template<size_t _C>
	Matrix<3, _C, T> Matrix<3, 3, T>::operator*(const Matrix<3, _C, T>& rhs) const
	{
		Matrix<3, _C, T> matrix;

		for (int index = 0; index < 3; ++index)
		{
			for (int jindex = 0; jindex < _C; ++jindex)
			{
				matrix[jindex][index] = std::move(T());
				for (int kindex = 0; kindex < 3; ++kindex)
					matrix[jindex][index] += (*this)[kindex][index] * rhs[jindex][kindex];
			}
		}
		return matrix;
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::operator*=(const Matrix<3, 3, T>& rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class T>
	Matrix<3, 3, T>& Matrix<3, 3, T>::operator*=(T rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<3, 3, T>& matrix)
	{
		for (int index = 0; index < 3; ++index)
		{
			for (int jindex = 0; jindex < 3; ++jindex)
				os << matrix[index][jindex] << '\t';

			os << '\n';
		}

		return os;
	}
}