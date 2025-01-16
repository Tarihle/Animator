#pragma once

#include "Transform.h"
#include "vector"

struct Animation
{
	Animation(const char* animName);

	std::vector<std::vector<Transform>> m_animFrameTransforms;
	size_t								m_keyFrameCount = 0;
	const char*							m_Name = nullptr;
};
