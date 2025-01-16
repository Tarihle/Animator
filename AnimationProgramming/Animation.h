#pragma once

#include "Transform.h"
#include "vector"

struct Animation
{
	Animation(const char* animName);

	void initTransforms(size_t boneCount);

	size_t								m_keyFrameCount = 0;
	const char*							m_Name = nullptr;
	std::vector<std::vector<Transform>> m_animFrameTransforms;
};
