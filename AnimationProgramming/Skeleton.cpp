#include "Skeleton.h"
#include "Engine.h"

Skeleton::Skeleton(size_t boneCount)
{
	m_Bones.reserve(boneCount);

	int middleIKAdjuster = 0;

	for (int i = 0; i < boneCount; i++)
	{
		if (!memcmp("ik_", GetSkeletonBoneName(i), 3))
		{
			middleIKAdjuster++;
			continue;
		}

		m_Bones.emplace_back(i, middleIKAdjuster);
	}
	m_Bones.shrink_to_fit();
	m_boneCount = m_Bones.size();
}