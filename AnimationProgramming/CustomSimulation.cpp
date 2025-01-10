#include "CustomSimulation.h"
#include "Transform.h"

#include <vector>

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

	printf("Spine bone index : %d\n", spine01);
	printf("Spine parent bone : %s\n", spineParentName);
	printf("Spine parent bone index : %d\n", spineParent);
	printf("Skeleton bone count: %d\n", GetSkeletonBoneCount());
	printf("Anim key count : %u\n", keyCount);
	printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
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

void CustomSimulation::drawSkeleton(int firstIndex, int lastIndex, LM_::Mat4 inverseBindMatrix)
{

}

void CustomSimulation::step1(float frameTime)
{
	std::vector<Transform> bones;
	size_t				   boneCount = GetSkeletonBoneCount() - 7;

	bones.reserve(boneCount);

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	for (int index = 0; index < boneCount; index++)
	{
		int parent = GetSkeletonBoneParentIndex(index);

		GetSkeletonBoneLocalBindTransform(index, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		bones.push_back({ { posX, posY, posZ }, { quatW, quatX, quatY, quatZ }, parent });

		if (parent != -1)
		{
			bones[index] *= bones[parent];
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}
