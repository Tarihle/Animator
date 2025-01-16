#include "Animation.h"
#include "Engine.h"

Animation::Animation(const char* animName)
{
	m_Name = animName;
	m_keyFrameCount = GetAnimKeyCount(animName);
	m_animFrameTransforms.reserve(m_keyFrameCount);
}

void Animation::initTransforms(size_t boneCount)
{
	for (int frame = 0; frame < m_keyFrameCount; frame++)
	{
		m_animFrameTransforms.push_back(std::vector<Transform>(boneCount));
		for (int boneIndex = 0; boneIndex < boneCount; boneIndex++)
		{
			GetAnimLocalBoneTransform(
				m_Name, boneIndex, frame, m_animFrameTransforms[frame][boneIndex].m_Position.m_x,
				m_animFrameTransforms[frame][boneIndex].m_Position.m_y, m_animFrameTransforms[frame][boneIndex].m_Position.m_z,
				m_animFrameTransforms[frame][boneIndex].m_Rotation.m_a, m_animFrameTransforms[frame][boneIndex].m_Rotation.m_b,
				m_animFrameTransforms[frame][boneIndex].m_Rotation.m_c, m_animFrameTransforms[frame][boneIndex].m_Rotation.m_d);
		}
	}
}
