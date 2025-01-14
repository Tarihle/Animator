#include "CustomSimulation.h"

LM_::Vec3 g_Origin(0.f);
LM_::Vec3 g_Red(1.f, 0.f, 0.f);
LM_::Vec3 g_Green(0.f, 1.f, 0.f);
LM_::Vec3 g_Blue(0.f, 0.f, 1.f);

int	  g_keyFrame = 0;
float g_timeAcc = 0.f;

void CustomSimulation::Init()
{
	float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	m_keyFrameCount = GetAnimKeyCount("ThirdPersonWalk.anim");

	size_t boneCount = GetSkeletonBoneCount();
	m_Bones.reserve(boneCount);
	m_animFrameTransforms.reserve(m_keyFrameCount);

	for (int frame = 0; frame < m_keyFrameCount; frame++)
	{
		m_animFrameTransforms.push_back(std::vector<Transform>(boneCount));
		// m_animFrameTransforms[frame].reserve(boneCount);
		for (int index = 0; index < boneCount; index++)
		{
			if (!memcmp("ik_", GetSkeletonBoneName(index), 3))
			{
				m_animFrameTransforms[frame].pop_back();
				continue;
			}

			int parent = GetSkeletonBoneParentIndex(index);

			GetAnimLocalBoneTransform(
				"ThirdPersonWalk.anim", index, frame, m_animFrameTransforms[frame][index].m_Position.m_x,
				m_animFrameTransforms[frame][index].m_Position.m_y, m_animFrameTransforms[frame][index].m_Position.m_z,
				m_animFrameTransforms[frame][index].m_Rotation.m_a, m_animFrameTransforms[frame][index].m_Rotation.m_b,
				m_animFrameTransforms[frame][index].m_Rotation.m_c, m_animFrameTransforms[frame][index].m_Rotation.m_d);

			if (frame == 0)
			{
				GetSkeletonBoneLocalBindTransform(index, posX, posY, posZ, quatW, quatX, quatY, quatZ);
				m_Bones.push_back({ { posX, posY, posZ }, { quatW, quatX, quatY, quatZ }, parent });
			}
		}
		m_animFrameTransforms[frame].shrink_to_fit();
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

std::vector<Transform> CustomSimulation::calculateTransforms(TransformType transformType)
{
	std::vector<Transform> bones = m_Bones;

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		if (transformType == TransformType::E_PALETTE)
		{
			bones[index] = m_animFrameTransforms[g_keyFrame][index] * bones[index];
		}
		if (parent != -1)
		{
			bones[index] *= bones[parent];
			bones[index].m_parentTransformIndex = parent;
		}
	}
	if (transformType == TransformType::E_INVERSEBINDPOSE)
	{
		for (int index = 0; index < bones.size(); index++)
		{
			bones[index] = -bones[index];
		}
	}

	return bones;
}

std::vector<LM_::Mat4> CustomSimulation::calculateMatrices(TransformType transformType)
{
	std::vector<Transform> bones = calculateTransforms(transformType);
	std::vector<LM_::Mat4> matrices(bones.size());

	for (int index = 0; index < bones.size(); index++)
	{
		matrices[index] = bones[index];
	}

	return matrices;
}

void CustomSimulation::drawSkeletonstep1()
{
	std::vector<Transform> bones = calculateTransforms(TransformType::E_BINDPOSE);

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		if (parent != -1)
		{
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

void CustomSimulation::drawSkeleton()
{
	std::vector<Transform> bones = calculateTransforms(TransformType::E_PALETTE);

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = bones[index].m_parentTransformIndex;

		if (parent != -1)
		{
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

void CustomSimulation::UpdateKeyFrameTime(float frameTime)
{
	if (g_timeAcc < (1.f / m_keyFrameCount))
	{
		g_timeAcc += frameTime;
	}
	else if (g_keyFrame < m_keyFrameCount - 1)
	{
		g_timeAcc = 0.f;
		++g_keyFrame;
	}
	else
	{
		g_timeAcc = 0.f;
		g_keyFrame = 0;
	}
}

void CustomSimulation::step1(float frameTime)
{
	drawSkeletonstep1();
}

void CustomSimulation::step2(float frameTime)
{
	UpdateKeyFrameTime(frameTime);

	drawSkeleton();
}

void CustomSimulation::step3(float frameTime)
{
	UpdateKeyFrameTime(frameTime);

	drawSkeleton();

	std::vector<LM_::Mat4> bonesPalette = calculateMatrices(TransformType::E_PALETTE);
	std::vector<LM_::Mat4> inverseBindPoses = calculateMatrices(TransformType::E_INVERSEBINDPOSE);
	std::vector<LM_::Mat4> skinMatrices;

	skinMatrices.reserve(inverseBindPoses.size());

	for (int i = 0; i < inverseBindPoses.size(); i++)
	{
		skinMatrices.push_back(bonesPalette[i] * inverseBindPoses[i]);
	}

	SetSkinningPose(&skinMatrices[0][0][0], skinMatrices.size());
}
