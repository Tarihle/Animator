#include "Transform.h"

Transform::Transform(void)
{
	m_Position = LM_::Vec3::zero();
	m_Rotation = LM_::Quaternion(0);
}

Transform::Transform(LM_::Vec3 pos, LM_::Quaternion rot, int parentIndex)
	: m_Position(pos), m_Rotation(rot), m_parentTransformIndex(parentIndex)
{
}

Transform::operator LM_::Mat4() const
{
	LM_::Quaternion copy(m_Rotation);

	if (!copy.isUnitQuaternion())
	{
		copy /= copy.magnitude();
	}

	float aSquared = copy.m_a * copy.m_a;
	float bSquared = copy.m_b * copy.m_b;
	float cSquared = copy.m_c * copy.m_c;
	float dSquared = copy.m_d * copy.m_d;

	float ab = copy.m_a * copy.m_b;
	float ac = copy.m_a * copy.m_c;
	float ad = copy.m_a * copy.m_d;

	float bc = copy.m_b * copy.m_c;
	float bd = copy.m_b * copy.m_d;

	float cd = copy.m_c * copy.m_d;

	///* STACK CORRUPTION */
	// return LM_::Mat4({ aSquared + bSquared - cSquared - dSquared, 2 * (bc - ad), 2 * (ac + bd), m_Position.m_x, 2 * (ad + bc),
	//				   aSquared - bSquared + cSquared - dSquared, 2 * (cd - ab), m_Position.m_y, 2 * (bd - ac), 2 * (ab + cd),
	//				   aSquared - bSquared - cSquared + dSquared, m_Position.m_z, 0.f, 0.f, 0.f, 1.f });

	LM_::Vec4 row1 = { aSquared + bSquared - cSquared - dSquared, 2 * (bc - ad), 2 * (ac + bd), m_Position.m_x };
	LM_::Vec4 row2 = { 2 * (ad + bc), aSquared - bSquared + cSquared - dSquared, 2 * (cd - ab), m_Position.m_y };
	LM_::Vec4 row3 = { 2 * (bd - ac), 2 * (ab + cd), aSquared - bSquared - cSquared + dSquared, m_Position.m_z };
	LM_::Vec4 row4 = { 0.f, 0.f, 0.f, 1.f };

	//LM_::Vec4 row1 = { aSquared + bSquared - cSquared - dSquared, 2 * (bc - ad), 2 * (ac + bd), 0.f };
	//LM_::Vec4 row2 = { 2 * (ad + bc), aSquared - bSquared + cSquared - dSquared, 2 * (cd - ab), 0.f };
	//LM_::Vec4 row3 = { 2 * (bd - ac), 2 * (ab + cd), aSquared - bSquared - cSquared + dSquared, 0.f };
	//LM_::Vec4 row4 = { m_Position.m_x, m_Position.m_y, m_Position.m_z, 1.f };

	return LM_::Mat4(row1, row2, row3, row4).GetTranspose();
}

Transform operator-(Transform const& pRight)
{
	return Transform(
		LM_::rotatePointVec3(LM_::conjugate(pRight.m_Rotation), pRight.m_Position) * -1, LM_::conjugate(pRight.m_Rotation),
		pRight.m_parentTransformIndex);
	//return Transform(pRight.m_Position * -1, LM_::conjugate(pRight.m_Rotation), pRight.m_parentTransformIndex);
}

Transform operator*(Transform pLeft, Transform const& pRight)
{
	return pLeft *= pRight;
}

Transform& operator*=(Transform& pLeftRef, Transform const& pRight)
{
	pLeftRef.m_Position = LM_::rotatePointVec3(pRight.m_Rotation, pLeftRef.m_Position) + pRight.m_Position;
	pLeftRef.m_Rotation = pRight.m_Rotation * pLeftRef.m_Rotation;
	return pLeftRef;
}
