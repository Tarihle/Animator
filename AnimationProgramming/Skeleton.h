#pragma once

#include "Bone.h"
#include "Transform.h"
#include "vector"

struct Skeleton
{
	Skeleton() = default;
	Skeleton(size_t boneCount);

	size_t				   m_boneCount = 0;
	std::vector<Bone>	   m_Bones;
	std::vector<LM_::Mat4> m_inverseBindPoses;
};