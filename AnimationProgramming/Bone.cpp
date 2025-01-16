#include "Bone.h"
#include "Engine.h"

Bone::Bone(int boneIndex, int parentIndexModifier)
{
	GetSkeletonBoneLocalBindTransform(
		boneIndex, m_localTransform.m_Position.m_x, m_localTransform.m_Position.m_y, m_localTransform.m_Position.m_z,
		m_localTransform.m_Rotation.m_a, m_localTransform.m_Rotation.m_b, m_localTransform.m_Rotation.m_c,
		m_localTransform.m_Rotation.m_d);

	m_parentIndex = GetSkeletonBoneParentIndex(boneIndex) - parentIndexModifier;

	m_Name = GetSkeletonBoneName(boneIndex);
}