#include "Transform.h"
#include "LibMath/Matrix/Mat4x4.h"

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
	LM_::Mat4 transMat = LM_::Mat4::Translate(m_Position);
	LM_::Mat4 quatMat = LM_::toRotationMat4(m_Rotation);

	return (transMat * quatMat);
}

Transform operator-(Transform const& pRight)
{
	return Transform(
		LM_::rotatePointVec3(LM_::conjugate(pRight.m_Rotation), pRight.m_Position) * -1, LM_::conjugate(pRight.m_Rotation),
		pRight.m_parentTransformIndex);
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
