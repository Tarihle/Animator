#pragma once

#include <LibMath/Matrix/Mat3x3.h>
#include <LibMath/Matrix/Mat4x4.h>

namespace LibMath
{
	template<class T>
	Matrix<4, 4, T>::Matrix(T v)
	{
		for (int index = 0; index < 4; ++index)
			for (int jindex = 0; jindex < 4; ++jindex)
				if (index == jindex) (*this)[index][jindex] = v;
				else (*this)[index][jindex] = T(0);
	}

	template<class T>
	Matrix<4, 4, T>::Matrix(const _RowType& a, const _RowType& b, const _RowType& c, const _RowType& d)
	{
		(*this)[0] = a;
		(*this)[1] = b;
		(*this)[2] = c;
		(*this)[3] = d;
	}

	template<class T>
	Matrix<4, 4, T>::Matrix(std::initializer_list<T> initList)
	{
		if (initList.size() != 4 * 4) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		size_t index = 0;
		for (auto& element : initList)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
				this->m_matrix[index][jindex] = std::move(element);

			++index;
		}
	}

	template<class T>
	Matrix<4, 4, T>::Matrix(std::initializer_list<std::initializer_list<T>> initList)
	{
		if (initList.size() != 4 || (initList.begin()->size() != 4)) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		int index = 0;
		for (auto& row : initList)
		{
			if (row.size() != 4)
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
	Matrix<4, 4, T> Matrix<4, 4, T>::Zero(void)
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
			for (int jindex = 0; jindex < 4; ++jindex)
				matrix[index][jindex] = T();

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Identity(void) requires(std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
			for (int jindex = 0; jindex < 4; ++jindex)
				matrix[index][jindex] = std::move((index == jindex) ? T(1) : T());

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Translate(const Vec3& translation) requires(std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();
		matrix[3][0] = translation[0];
		matrix[3][1] = translation[1];
		matrix[3][2] = translation[2];

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Rotate(const Vec3& rotation) requires(std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> rotate = Matrix<4, 4, T>::Identity();
		Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

		matrix[1][1] = std::cosf(rotation[0]);
		matrix[2][2] = std::cosf(rotation[0]);

		matrix[2][1] = std::sinf(rotation[0]);
		matrix[1][2] = -std::sinf(rotation[0]);

		rotate *= matrix;

		matrix.ToIdentity();

		matrix[0][0] = std::cosf(rotation[1]);
		matrix[2][2] = std::cosf(rotation[1]);

		matrix[0][2] = -std::sinf(rotation[1]);
		matrix[2][0] = std::sinf(rotation[1]);

		rotate *= matrix;

		matrix.ToIdentity();

		matrix[0][0] = std::cosf(rotation[2]);
		matrix[1][1] = std::cosf(rotation[2]);

		matrix[0][1] = std::sinf(rotation[2]);
		matrix[1][0] = -std::sinf(rotation[2]);

		rotate *= matrix;
		return rotate;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Scale(const Vec3& scale) requires (std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();
		matrix[0][0] = scale[0];
		matrix[1][1] = scale[1];
		matrix[2][2] = scale[2];

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Perspective(T fov, T aspect, T near, T far) requires (std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Zero();

		const T S = std::tan(fov / static_cast<T>(2));

		matrix[0][0] = static_cast<T>(1) / (aspect * S);
		matrix[1][1] = static_cast<T>(1) / (S);
		matrix[2][2] = - (far + near) / (far - near);
		matrix[2][3] = - static_cast<T>(1);
		matrix[3][2] = - (static_cast<T>(2) * far * near) / (far - near);

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Ortho(T left, T right, T bottom, T top) requires (std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

		matrix[0][0] = static_cast<T>(2) / (right - left);
		matrix[1][1] = static_cast<T>(2) / (top - bottom);
		matrix[2][2] = -static_cast<T>(1);
		matrix[3][0] = -(right + left) / (right - left);
		matrix[3][1] = -(top + bottom) / (top - bottom);

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::Ortho(T left, T right, T bottom, T top, T near, T far) requires (std::is_arithmetic_v<T>)
	{
		Matrix<4, 4, T> matrix = Matrix<4, 4, T>::Identity();

		matrix[0][0] = static_cast<T>(2) / (right - left);
		matrix[1][1] = static_cast<T>(2) / (top - bottom);
		matrix[2][2] = -static_cast<T>(2) / (far - near);
		matrix[3][0] = -(right + left) / (right - left);
		matrix[3][1] = -(top + bottom) / (top - bottom);
		matrix[3][2] = -(far + near) / (far - near);

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::LookAt(const LibMath::Vec3& eye, const LibMath::Vec3& center, const LibMath::Vec3& up)
	{
		LibMath::Mat4 mat = LibMath::Mat4::Identity();

		LibMath::Vec3 f = LibMath::Vec3(center - eye).normalize();
		LibMath::Vec3 s = LibMath::Vec3(up.cross(f)).normalize();
		LibMath::Vec3 u = f.cross(s);

		mat[0][0] = s.m_x;
		mat[1][0] = s.m_y;
		mat[2][0] = s.m_z;

		mat[0][1] = u.m_x;
		mat[1][1] = u.m_y;
		mat[2][1] = u.m_z;

		mat[0][2] = f.m_x;
		mat[1][2] = f.m_y;
		mat[2][2] = f.m_z;

		mat[3][0] = -s.dot(eye);
		mat[3][1] = -u.dot(eye);
		mat[3][2] = -f.dot(eye);

		return mat;
	}

	template<class T>
	bool Matrix<4, 4, T>::operator==(const LibMath::Matrix<4, 4, T>& rhs) const requires(std::is_arithmetic_v<T>)
	{
		return this->m_matrix[0] == rhs.m_matrix[0]
			&& this->m_matrix[1] == rhs.m_matrix[1]
			&& this->m_matrix[2] == rhs.m_matrix[2]
			&& this->m_matrix[3] == rhs.m_matrix[3];
	}

	template <class T>
	bool Matrix<4, 4, T>::operator!=(const LibMath::Matrix<4, 4, T>& rhs) const requires(std::is_arithmetic_v<T>)
	{
		return this->m_matrix[0] != rhs.m_matrix[0] 
			|| this->m_matrix[1] != rhs.m_matrix[1] 
			|| this->m_matrix[2] != rhs.m_matrix[2] 
			|| this->m_matrix[3] != rhs.m_matrix[3];
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::ToIdentity(void)
		requires (std::is_arithmetic_v<T>)
	{
		for (int index = 0; index < 4; ++index)
			for (int jindex = 0; jindex < 4; ++jindex)
				(*this)[index][jindex] = std::move((index == jindex) ? T(1) : T());

		return *this;
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::Empty(void)
	{
		for (int index = 0; index < 4; ++index)
			for (int jindex = 0; jindex < 4; ++jindex)
				(*this)[index][jindex] = std::move(T());

		return *this;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::GetTranspose(void) const
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
			for (int jindex = 0; jindex < 4; ++jindex)
				matrix[jindex][index] = (*this)[index][jindex];

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::ToTranspose(void)
	{
		*this = std::move(this->GetTranspose());
		return *this;
	}

	template<class T>
	T Matrix<4, 4, T>::GetDeterminant(void) const
	{
		T determinant = T();

		for (int index = 0; index < 4; ++index)
		{
			Matrix<3, 3, T> matrix = std::move(this->GetMinor(index, 0));
			determinant += ((index) % 2 > 0 ? -1 : 1) * (*this)[index][0] * matrix.GetDeterminant();
		}

		return determinant;
	}

	template<class T>
	Matrix<3, 3, T> Matrix<4, 4, T>::GetMinor(size_t row, size_t column) const
	{
		Matrix<3, 3, T> matrix;

		size_t zindex = 0;
		for (int index = 0; index < 4; ++index)
		{
			int kindex = 0;
			for (int jindex = 0; jindex < 4; ++jindex)
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
	Matrix<4, 4, T> Matrix<4, 4, T>::GetMinorsDeterminant(void) const
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = this->GetMinor(index, jindex).GetDeterminant();
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::GetCofactors(void) const
	{
		Matrix<4, 4, T> matrix = std::move(this->GetMinorsDeterminant());

		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] *= ((index + jindex) % 2 > 0 ? -1 : 1);
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::GetInverse(void) const
	{
		Matrix<4, 4, T> matrix = this->GetCofactors().ToTranspose();
		matrix *= (1 / this->GetDeterminant());

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::operator*(T rhs) const
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = (*this)[index][jindex] * rhs;
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::operator+(const Matrix<4, 4, T>& rhs) const
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = (*this)[index][jindex] + rhs[index][jindex];
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::operator+=(const Matrix<4, 4, T>& rhs)
	{
		*this = std::move(this->operator+(rhs));
		return *this;
	}

	template<class T>
	Matrix<4, 4, T> Matrix<4, 4, T>::operator-(const Matrix<4, 4, T>& rhs) const
	{
		Matrix<4, 4, T> matrix;

		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
			{
				matrix[index][jindex] = (*this)[index][jindex] - rhs[index][jindex];
			}
		}

		return matrix;
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::operator-=(const Matrix<4, 4, T>& rhs)
	{
		*this = std::move(this->operator-(rhs));
		return *this;
	}

	template<class T>
	template<size_t _C>
	Matrix<4, _C, T> Matrix<4, 4, T>::operator*(const Matrix<4, _C, T>& rhs) const
	{
		Matrix<4, _C, T> matrix;

		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < _C; ++jindex)
			{
				matrix[jindex][index] = std::move(T());
				for (int kindex = 0; kindex < 4; ++kindex)
					matrix[jindex][index] += (*this)[kindex][index] * rhs[jindex][kindex];
			}
		}
		return matrix;
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::operator*=(const Matrix<4, 4, T>& rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class T>
	Matrix<4, 4, T>& Matrix<4, 4, T>::operator*=(T rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class T>
	Vec4 operator*(const Vec4& vec, const Matrix<4, 4, T>& matrix)
	{
		LibMath::Vec4 vector = LibMath::Vec4::Zero();

		for (int index = 0; index < 4; ++index)
		{
			vector[index] = static_cast<T>(0);
			for (int kindex = 0; kindex < 4; ++kindex)
				vector[index] += matrix[kindex][index] * vec[kindex];
		}

		return vector;
	}

	template <class T> requires(std::is_arithmetic_v<T>)
	Vec4 operator*(const Vec4& vec, const Matrix<4, 4, T>& mat) 
	{
		Vec4 result = Vec4::zero();

		for (uint32_t idx = 0; idx < 4; ++idx) {
			result[idx] = static_cast<T>(0);
			for (uint32_t kdx = 0; kdx < 4; ++kdx)
				result[idx] += mat[kdx][idx] * vec[kdx];
		}
		return result;
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const Matrix<4, 4, T>& matrix)
	{
		for (int index = 0; index < 4; ++index)
		{
			for (int jindex = 0; jindex < 4; ++jindex)
				os << matrix[index][jindex] << '\t';

			os << '\n';
		}

		return os;
	}
}