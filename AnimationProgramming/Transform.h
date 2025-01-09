#pragma once

#include "pch.h"

struct Transform
{
	LM_::Vec3 m_Position;
	LM_::Quaternion m_Rotation;

	operator LM_::Mat4() const;
};

Transform operator-(Transform const& pRight);

Transform operator*(Transform pLeft, Transform const& pRight);

Transform& operator*=(Transform& pLeftRef, Transform const& pRight);

Transform interpolate(Transform const& pLeft, Transform const& pRight, float pAlpha);
