#include "CustomSimulation.h"

LM_::Vec3 g_Origin(0.f);
LM_::Vec3 g_Red(1.f, 0.f, 0.f);
LM_::Vec3 g_Green(0.f, 1.f, 0.f);
LM_::Vec3 g_Blue(0.f, 0.f, 1.f);

int	   g_keyFrame = 0;
float  g_timeAcc = 0.f;
float  g_timeAccTest = 0.f;
size_t g_fps = 0;

void CustomSimulation::Init()
{
	m_Animations.push_back(Animation("ThirdPersonWalk.anim"));
	m_Animations.push_back(Animation("ThirdPersonRun.anim"));
	//float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	size_t boneCount = GetSkeletonBoneCount();
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

	for (int animIndex = 0; animIndex < m_Animations.size(); animIndex++)
	{
		for (int frame = 0; frame < m_Animations[animIndex].m_keyFrameCount; frame++)
		{
			m_Animations[animIndex].m_animFrameTransforms.push_back(std::vector<Transform>(m_boneCount));
			for (int boneIndex = 0; boneIndex < m_boneCount; boneIndex++)
			{
				GetAnimLocalBoneTransform(
					m_Animations[animIndex].m_Name, boneIndex, frame,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Position.m_x,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Position.m_y,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Position.m_z,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Rotation.m_a,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Rotation.m_b,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Rotation.m_c,
					m_Animations[animIndex].m_animFrameTransforms[frame][boneIndex].m_Rotation.m_d);
			}
		}
	}
}

void CustomSimulation::Update(float frameTime)
{
	if (frameTime > 0.1f)
	{
		frameTime = 1.0f / 60.0f;
	}
	// frameTime /= 10.0f;

	drawWorldMarker();

	// step1(frameTime);
	// step2(frameTime);
	// step3(frameTime);
	step4(frameTime);
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
	std::vector<Transform> bones(m_boneCount);

	for (int index = 0; index < bones.size(); index++)
	{
		bones[index] = m_Bones[index].m_localTransform;

		if (transformType == TransformType::E_PALETTE)
		{
			bones[index] = m_Animations[0].m_animFrameTransforms[g_keyFrame][index] * bones[index];
		}
		if (m_Bones[index].m_parentIndex != -1)
		{
			bones[index] *= bones[m_Bones[index].m_parentIndex];
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

std::vector<Transform> CustomSimulation::calculateInterpolatedTransforms(float lerpRatio)
{
	std::vector<Transform> bones(m_boneCount);
	// std::cout << g_keyFrame << std::endl;

	for (int index = 0; index < m_boneCount; index++)
	{
		bones[index] = m_Bones[index].m_localTransform;

		int		  nextKeyFrame = (g_keyFrame + 1) % m_Animations[0].m_keyFrameCount;
		Transform currentFrameBone = m_Animations[0].m_animFrameTransforms[g_keyFrame][index] * bones[index];
		Transform nextFrameBone = m_Animations[0].m_animFrameTransforms[nextKeyFrame][index] * bones[index];
		bones[index] = interpolate(currentFrameBone, nextFrameBone, lerpRatio);

		if (m_Bones[index].m_parentIndex != -1)
		{
			bones[index] *= bones[m_Bones[index].m_parentIndex];
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
		if (m_Bones[index].m_parentIndex != -1)
		{
			drawLine(
				bones[index].m_Position, bones[m_Bones[index].m_parentIndex].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

void CustomSimulation::drawSkeleton()
{
	std::vector<Transform> bones = calculateTransforms(TransformType::E_PALETTE);

	for (int index = 0; index < bones.size(); index++)
	{
		if (m_Bones[index].m_parentIndex != -1)
		{
			drawLine(
				bones[index].m_Position, bones[m_Bones[index].m_parentIndex].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

void CustomSimulation::drawSkeletonSmooth(float frameTime)
{
	std::vector<Transform> bones = calculateInterpolatedTransforms(frameTime);

	for (int index = 0; index < bones.size(); index++)
	{
		if (m_Bones[index].m_parentIndex != -1)
		{
			drawLine(
				bones[index].m_Position, bones[m_Bones[index].m_parentIndex].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

void CustomSimulation::updateKeyFrameTime(float frameTime)
{
	if (g_timeAcc < (1.f / m_Animations[0].m_keyFrameCount))
	{
		g_timeAcc += frameTime;
	}
	else if (g_keyFrame < m_Animations[0].m_keyFrameCount - 1)
	{
		g_timeAcc = 0.f;
		++g_keyFrame;
	}
	else
	{
		g_timeAcc = 0.f;
		g_keyFrame = 0;
		std::cout << g_fps << std::endl;
		g_fps = 0;
	}
	g_fps++;

	g_timeAccTest += frameTime;
	if (g_timeAccTest >= 1.0f)
	{
		g_timeAccTest -= 1.0f;
	}
}

void CustomSimulation::step1(float frameTime)
{
	drawSkeletonstep1();
}

void CustomSimulation::step2(float frameTime)
{
	updateKeyFrameTime(frameTime);

	drawSkeleton();
}

void CustomSimulation::step3(float frameTime)
{
	updateKeyFrameTime(frameTime);

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

void CustomSimulation::step4(float frameTime)
{
	updateKeyFrameTime(frameTime);

	// drawSkeletonSmooth(g_timeAccTest);
	drawSkeletonSmooth(g_timeAcc * m_Animations[0].m_keyFrameCount);
	// drawSkeleton();

	// std::vector<LM_::Mat4> bonesPalette = calculateMatrices(TransformType::E_PALETTE);
	std::vector<Transform> bonesPalette = calculateInterpolatedTransforms(g_timeAcc * m_Animations[0].m_keyFrameCount);
	std::vector<LM_::Mat4> inverseBindPoses = calculateMatrices(TransformType::E_INVERSEBINDPOSE);
	std::vector<LM_::Mat4> skinMatrices;

	skinMatrices.reserve(inverseBindPoses.size());

	for (int i = 0; i < inverseBindPoses.size(); i++)
	{
		skinMatrices.push_back(LM_::Mat4(bonesPalette[i]) * inverseBindPoses[i]);
	}

	SetSkinningPose(&skinMatrices[0][0][0], skinMatrices.size());
}

void CustomSimulation::step5(float frameTime)
{
	updateKeyFrameTime(frameTime);
	// drawSkeletonSmooth(g_timeAcc * m_keyFrameWalkCount);
}
