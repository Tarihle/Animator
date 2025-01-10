#include "CustomSimulation.h"

LM_::Vec3 g_Origin(0.f);
LM_::Vec3 g_Red(1.f, 0.f, 0.f);
LM_::Vec3 g_Green(0.f, 1.f, 0.f);
LM_::Vec3 g_Blue(0.f, 0.f, 1.f);

void CustomSimulation::Init()
{
	int			spine01 = GetSkeletonBoneIndex("spine_01");
	int			spineParent = GetSkeletonBoneParentIndex(spine01);
	const char* spineParentName = GetSkeletonBoneName(spineParent);

	float  posX, posY, posZ, quatW, quatX, quatY, quatZ;
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount * 0.5f, posX, posY, posZ, quatW, quatX, quatY, quatZ);

	// printf("Spine bone index : %d\n", spine01);
	// printf("Spine parent bone : %s\n", spineParentName);
	// printf("Spine parent bone index : %d\n", spineParent);
	// printf("Skeleton bone count: %d\n", GetSkeletonBoneCount());
	// printf("Anim key count : %u\n", keyCount);
	// printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY,
	// quatZ);

	size_t boneCount = GetSkeletonBoneCount();
	m_Bones.reserve(boneCount);

	for (int index = 0; index < boneCount; index++)
	{
		if (!memcmp("ik_", GetSkeletonBoneName(index), 3))
		{
			continue;
		}

		int parent = GetSkeletonBoneParentIndex(index);

		GetSkeletonBoneLocalBindTransform(index, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		m_Bones.push_back({ { posX, posY, posZ }, { quatW, quatX, quatY, quatZ }, parent });

		if (parent != -1)
		{
			m_Bones[index] *= m_Bones[parent];
		}
	}

	m_Bones.shrink_to_fit();
}

void CustomSimulation::Update(float frameTime)
{
	if (frameTime > 0.1f)
	{
		frameTime = 1.0f / 60.0f;
	}
	// frameTime /= 100.0f;

	drawWorldMarker();

	step1(frameTime);
	// step2(frameTime);
	// step3(frameTime);
	// step4(frameTime);
	// step5(frameTime);
}

void CustomSimulation::drawWorldMarker()
{
	drawLine(g_Origin, { 100.f, 0, 0 }, g_Red);	  // X axis
	drawLine(g_Origin, { 0, 100.f, 0 }, g_Green); // Y axis
	drawLine(g_Origin, { 0, 0, 100.f }, g_Blue);  // Z axis
}

void CustomSimulation::drawLine(
	LM_::Vec3 const& pStart, LM_::Vec3 const& pEnd, LM_::Vec3 const& pColor, LM_::Vec3 const& pOffset) const
{
	::DrawLine(
		pStart.m_x + pOffset.m_x, pStart.m_y + pOffset.m_y, pStart.m_z + pOffset.m_z, pEnd.m_x + pOffset.m_x,
		pEnd.m_y + pOffset.m_y, pEnd.m_z + pOffset.m_z, pColor.m_x, pColor.m_y, pColor.m_z);
}

void CustomSimulation::drawSkeleton()
{
	for (auto bone : m_Bones)
	{
		if (bone.m_parentTransformIndex != -1)
		{
			drawLine(bone.m_Position, m_Bones[bone.m_parentTransformIndex].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

void CustomSimulation::step1(float frameTime)
{
	drawSkeleton();
}
