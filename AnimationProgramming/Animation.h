#pragma once

#include "Transform.h"
#include "vector"

struct Animation
{
	Animation(const char* animName);

	void initTransforms(size_t boneCount);

	size_t								m_keyFrameCount = 0;
	unsigned int						m_keyFrame = 0;
	float								m_timeAcc = 0.f;
	const char*							m_Name = nullptr;
	std::vector<std::vector<Transform>> m_animFrameTransforms;
};
