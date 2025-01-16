#pragma once

#include "Transform.h"
#include "vector"

struct Bone
{
	Bone(int boneIndex, int parentIndexModifier);

	int			m_parentIndex = 0;
	const char* m_Name = nullptr;
	Transform	m_localTransform;
};