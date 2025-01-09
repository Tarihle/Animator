#pragma once

#include <LibMath/Matrix/Mat2x2.h>

namespace LibMath
{
	template<class T>
	Matrix<2, 2, T>::Matrix(T v)
	{
		for (int index = 0; index < 2; ++index)
			for (int jindex = 0; jindex < 2; ++jindex)
				if (index == jindex) (*this)[index][jindex] = v;
				else (*this)[index][jindex] = T(0);
	}

	template<class T>
	Matrix<2, 2, T>::Matrix(const _RowType& a, const _RowType& b)
	{
		(*this)[0] = a;
		(*this)[1] = b;
	}

	template<class T>
	Matrix<2, 2, T>::Matrix(std::initializer_list<T> initList)
	{
		if (initList.size() != 2 * 2) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		int index = 0;
		for (auto& element : initList)
		{
			for (int jindex = 0; jindex < 2; ++jindex)
				this->m_matrix[index][jindex] = std::move(element);

			++index;
		}
	}

	template<class T>
	Matrix<2, 2, T>::Matrix(std::initializer_list<std::initializer_list<T>> initList)
	{
		if (initList.size() != 2 || (initList.begin()->size() != 2)) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		int index = 0;
		for (auto& row : initList)
		{
			if (row.size() != 2)
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
	Matrix<2, 2, T> Matrix<2, 2, T>::Zero(void)
	{
		Matrix<2, 2, T> matrix;

		for (int index = 0; index < 2; ++index)
			for (int jindex = 0; jindex < 2; ++jindex)
				matrix[index][jindex] = T();

		return matrix;
	}

	template<class T>
	Matrix<2, 2, T> Matrix<2, 2, T>::Identity(void) requires (std::is_arithmetic_v<T>)
	{
		Matrix<2, 2, T> matrix;

		for (int index = 0; index < 2; ++index)
			for (int jindex = 0; jindex < 2; ++jindex)
				matrix[index][jindex] = std::move((index == jindex) ? T(1) : T());

		return matrix;
	}

	template<class T>
	bool Matrix<2, 2, T>::operator==(const Matrix<2, 2, T>& rhs) const requires(std::is_arithmetic_v<T>)
	{
		return this->m_matrix[0] == rhs.m_matrix[0]
			&& this->m_matrix[1] == rhs.m_matrix[1];
	}

	template<class T>
	bool Matrix<2, 2, T>::operator!=(const Matrix<2, 2, T>& rhs) const requires(std::is_arithmetic_v<T>)
	{
		return this->m_matrix[0] != rhs.m_matrix[0]
			|| this->m_matrix[1] != rhs.m_matrix[1];
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::ToIdentity(void)
		requires (std::is_arithmetic_v<T>)
	{
		for (int index = 0; index < 2; ++index)
			for (int jindex = 0; jindex < 2; ++jindex)
				(*this)[index][jindex] = std::move((index == jindex) ? T(1) : T());

		return *this;
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::Empty(void)
	{
		for (int index = 0; index < 2; ++index)
			for (int jindex = 0; jindex < 2; ++jindex)
				(*this)[index][jindex] = std::move(T());

		return *this;
	}

	template<class T>
	Matrix<2, 2, T> Matrix<2, 2, T>::GetTranspose(void) const
	{
		Matrix<2, 2, T> matrix;

		for (int index = 0; index < 2; ++index)
			for (int jindex = 0; jindex < 2; ++jindex)
				matrix[jindex][index] = (*this)[index][jindex];

		return matrix;
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::ToTranspose(void)
	{
		*this = std::move(this->GetTranspose());
		return *this;
	}

	template<class T>
	T Matrix<2, 2, T>::GetDeterminant(void) const
	{
		return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);
	}

	template<class T>
	T Matrix<2, 2, T>::GetMinor(int row, int column) const
	{
		int zindex = 0;
		for (int index = 0; index < 2; ++index)
		{
			int kindex = 0;
			for (int jindex = 0; jindex < 2; ++jindex)
			{
				if (index == row || jindex == column) continue;

				return (*this)[index][jindex];
			}
		}

		return T(0);
	}

	template<class T>
	Matrix<2, 2, T> Matrix<2, 2, T>::operator*(T rhs) const
	{
		Matrix<2, 2, T> matrix = *this;

		for (int index = 0; index < 2; ++index)
			matrix[index] *= rhs;

		return matrix;
	}

	template<class T>
	Matrix<2, 2, T> Matrix<2, 2, T>::operator+(const Matrix<2, 2, T>& rhs) const
	{
		Matrix<2, 2, T> matrix = *this;

		for (int index = 0; index < 2; ++index)
			matrix[index] += rhs[index];

		return matrix;
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::operator+=(const Matrix<2, 2, T>& rhs)
	{
		*this = std::move(this->operator+(rhs));
		return *this;
	}

	template<class T>
	Matrix<2, 2, T> Matrix<2, 2, T>::operator-(const Matrix<2, 2, T>& rhs) const
	{
		Matrix<2, 2, T> matrix = *this;

		for (int index = 0; index < 2; ++index)
			matrix[index] -= rhs[index];

		return matrix;
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::operator-=(const Matrix<2, 2, T>& rhs)
	{
		*this = std::move(this->operator-(rhs));
		return *this;
	}

	template<class T>
	template<size_t _C>
	Matrix<2, _C, T> Matrix<2, 2, T>::operator*(const Matrix<2, _C, T>& rhs) const
	{
		Matrix<2, _C, T> matrix;

		for (int index = 0; index < 2; ++index)
		{
			for (int jindex = 0; jindex < _C; ++jindex)
			{
				matrix[jindex][index] = std::move(T());
				for (int kindex = 0; kindex < 2; ++kindex)
					matrix[jindex][index] += (*this)[kindex][index] * rhs[jindex][kindex];
			}
		}
		return matrix;
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::operator*=(const Matrix<2, 2, T>& rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class T>
	Matrix<2, 2, T>& Matrix<2, 2, T>::operator*=(T rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<2, 2, T>& matrix)
	{
		for (int index = 0; index < 2; ++index)
		{
			for (int jindex = 0; jindex < 2; ++jindex)
				os << matrix[index][jindex] << '\t';

			os << '\n';
		}

		return os;
	}
}