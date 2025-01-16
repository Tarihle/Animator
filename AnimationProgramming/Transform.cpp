#include "Transform.h"

Transform::Transform(void)
{
	m_Position = LM_::Vec3::zero();
	m_Rotation = LM_::Quaternion(0);
}

Transform::Transform(LM_::Vec3 pos, LM_::Quaternion rot)
	: m_Position(pos), m_Rotation(rot)
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
		LM_::rotatePointVec3(LM_::conjugate(pRight.m_Rotation), pRight.m_Position) * -1, LM_::conjugate(pRight.m_Rotation));
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

Transform interpolate(Transform const& pLeft, Transform const& pRight, float pAlpha)
{
	return Transform(LM_::Lerp(pLeft.m_Position, pRight.m_Position, pAlpha), LM_::slerp(pLeft.m_Rotation, pRight.m_Rotation, pAlpha));
}
