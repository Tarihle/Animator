#include "Animation.h"
#include "Engine.h"

Animation::Animation(const char* animName)
{
	m_Name = animName;
	m_keyFrameCount = GetAnimKeyCount(animName);
	m_animFrameTransforms.reserve(m_keyFrameCount);
}
