#include "CustomSimulation.h"

LM_::Vec3 g_Origin(0.f);
LM_::Vec3 g_Red(1.f, 0.f, 0.f);
LM_::Vec3 g_Green(0.f, 1.f, 0.f);
LM_::Vec3 g_Blue(0.f, 0.f, 1.f);

int	  g_keyFrame = 0;
float g_timeAcc = 0.f;

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
	}

	m_Bones.shrink_to_fit();

	Transform test = { { -410, -450, 260 }, { 0.844623, -0.191342, -0.46194, 0.191342 }, 0 };
	Transform inverted = -test;
	LM_::Mat4 testMat = LM_::Mat4(test).GetInverse();
	LM_::Mat4 invertedMat = LM_::Mat4(inverted);

	float oui;
}

void CustomSimulation::Update(float frameTime)
{
	if (frameTime > 0.1f)
	{
		frameTime = 1.0f / 60.0f;
	}
	// frameTime /= 100.0f;

	drawWorldMarker();

	// step1(frameTime);
	// step2(frameTime);
	step3(frameTime);
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

std::vector<LM_::Mat4> CustomSimulation::calculateInverseBindPoseMatrices(void)
{
	std::vector<Transform> bones = m_Bones;
	std::vector<LM_::Mat4> matrices(bones.size());

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		if (parent != -1)
		{
			bones[index] *= bones[parent];
		}
		 matrices[index] = -bones[index];
		//matrices[index] = LM_::Mat4(bones[index]).GetInverse();
	}
	return matrices;
}

std::vector<LM_::Mat4> CustomSimulation::calculatePaletteMatrices(void)
{
	std::vector<Transform> bones = m_Bones;
	std::vector<LM_::Mat4> matrices(bones.size());

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", index, g_keyFrame, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		Transform animLocalChildTransform({ { posX, posY, posZ }, { quatW, quatX, quatY, quatZ }, parent });

		bones[index] = animLocalChildTransform * bones[index];
		if (parent != -1)
		{
			bones[index] *= bones[parent];
		}
		matrices[index] = bones[index];
		//matrices[index] = matrices[index].GetInverse();
	}

	return matrices;
}

void CustomSimulation::drawSkeletonstep1()
{
	std::vector<Transform> bones = m_Bones;

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		if (parent != -1)
		{
			bones[index] *= bones[parent];
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

std::vector<Transform> CustomSimulation::drawSkeleton()
{
	std::vector<Transform> bones = m_Bones;

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		GetAnimLocalBoneTransform("ThirdPersonWalk.anim", index, g_keyFrame, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		Transform animLocalChildTransform({ { posX, posY, posZ }, { quatW, quatX, quatY, quatZ }, parent });

		if (parent != -1)
		{
			bones[index] = animLocalChildTransform * bones[index];
			bones[index] *= bones[parent];
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}

	return bones;
}

void CustomSimulation::step1(float frameTime)
{
	drawSkeletonstep1();
}

void CustomSimulation::step2(float frameTime)
{
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");

	if (g_timeAcc < (1.f / keyCount))
	{
		g_timeAcc += frameTime;
	}
	else if (g_keyFrame < keyCount - 1)
	{
		g_timeAcc = 0.f;
		++g_keyFrame;
	}
	else
	{
		g_timeAcc = 0.f;
		g_keyFrame = 0;
	}

	drawSkeleton();
}

void CustomSimulation::step3(float frameTime)
{
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");

	if (g_timeAcc < (1.f / keyCount))
	{
		g_timeAcc += frameTime;
	}
	else if (g_keyFrame < keyCount - 1)
	{
		g_timeAcc = 0.f;
		++g_keyFrame;
	}
	else
	{
		g_timeAcc = 0.f;
		g_keyFrame = 0;
	}

	drawSkeleton();

	std::vector<LM_::Mat4> bonesPalette = calculatePaletteMatrices();
	std::vector<LM_::Mat4> inverseBindPoses = calculateInverseBindPoseMatrices();
	std::vector<LM_::Mat4> skinMatrices;

	skinMatrices.reserve(inverseBindPoses.size());

	for (int i = 0; i < inverseBindPoses.size(); i++)
	{
		// skinMatrices.push_back(inverseBindPoses[i] * bonesPalette[i]);
		skinMatrices.push_back(bonesPalette[i] * inverseBindPoses[i]);
	}

	SetSkinningPose(&skinMatrices[0][0][0], skinMatrices.size());
}
