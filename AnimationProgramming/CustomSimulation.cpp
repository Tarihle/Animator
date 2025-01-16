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
	size_t boneCount = GetSkeletonBoneCount();
	m_Skeleton = Skeleton(boneCount);

	m_Animations.push_back(Animation("ThirdPersonWalk.anim"));
	m_Animations.push_back(Animation("ThirdPersonRun.anim"));

	for (int animIndex = 0; animIndex < m_Animations.size(); animIndex++)
	{
		m_Animations[animIndex].initTransforms(m_Skeleton.m_boneCount);
	}

	m_Skeleton.m_inverseBindPoses = calculateMatrices(TransformType::E_INVERSEBINDPOSE);
}

void CustomSimulation::Update(float frameTime)
{
	if (frameTime > 0.1f)
	{
		frameTime = 1.0f / 60.0f;
	}
	 //frameTime /= 10.0f;

	drawWorldMarker();

	 //step1(frameTime);
	 //step2(frameTime);
	 //step3(frameTime);
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

std::vector<Transform> CustomSimulation::calculateTransforms(TransformType transformType, float lerpRatio)
{
	std::vector<Transform> bones(m_Skeleton.m_boneCount);

	for (int index = 0; index < bones.size(); index++)
	{
		bones[index] = m_Skeleton.m_Bones[index].m_localTransform;

		if (transformType == TransformType::E_PALETTE)
		{
			bones[index] = m_Animations[0].m_animFrameTransforms[g_keyFrame][index] * bones[index];
		}
		else if (transformType == TransformType::E_INTERPOLATEDPALETTE)
		{
			int		  nextKeyFrame = (g_keyFrame + 1) % m_Animations[0].m_keyFrameCount;
			Transform currentFrameBone = m_Animations[0].m_animFrameTransforms[g_keyFrame][index] * bones[index];
			Transform nextFrameBone = m_Animations[0].m_animFrameTransforms[nextKeyFrame][index] * bones[index];
			bones[index] = interpolate(currentFrameBone, nextFrameBone, lerpRatio);
		}

		int parent = m_Skeleton.m_Bones[index].m_parentIndex;
		if (parent != -1)
		{
			bones[index] *= bones[parent];
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

void CustomSimulation::drawSkeleton(TransformType transformType, float lerpRatio)
{
	std::vector<Transform> bones = calculateTransforms(transformType, lerpRatio);

	for (int index = 0; index < bones.size(); index++)
	{
		int parent = m_Skeleton.m_Bones[index].m_parentIndex;
		if (parent != -1)
		{
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
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
	drawSkeleton(TransformType::E_BINDPOSE);
}

void CustomSimulation::step2(float frameTime)
{
	updateKeyFrameTime(frameTime);

	drawSkeleton(TransformType::E_PALETTE);
}

void CustomSimulation::step3(float frameTime)
{
	updateKeyFrameTime(frameTime);

	drawSkeleton(TransformType::E_PALETTE);

	std::vector<LM_::Mat4> bonesPalette = calculateMatrices(TransformType::E_PALETTE);
	std::vector<LM_::Mat4> skinMatrices;

	skinMatrices.reserve(m_Skeleton.m_inverseBindPoses.size());

	for (int i = 0; i < m_Skeleton.m_inverseBindPoses.size(); i++)
	{
		skinMatrices.push_back(bonesPalette[i] * m_Skeleton.m_inverseBindPoses[i]);
	}

	SetSkinningPose(&skinMatrices[0][0][0], skinMatrices.size());
}

void CustomSimulation::step4(float frameTime)
{
	updateKeyFrameTime(frameTime);

	drawSkeleton(TransformType::E_INTERPOLATEDPALETTE, g_timeAcc * m_Animations[0].m_keyFrameCount);

	std::vector<Transform> bonesPalette =
		calculateTransforms(TransformType::E_INTERPOLATEDPALETTE, g_timeAcc * m_Animations[0].m_keyFrameCount);
	std::vector<LM_::Mat4> skinMatrices;

	skinMatrices.reserve(m_Skeleton.m_inverseBindPoses.size());

	for (int i = 0; i < m_Skeleton.m_inverseBindPoses.size(); i++)
	{
		skinMatrices.push_back(LM_::Mat4(bonesPalette[i]) * m_Skeleton.m_inverseBindPoses[i]);
	}

	SetSkinningPose(&skinMatrices[0][0][0], skinMatrices.size());
}

void CustomSimulation::step5(float frameTime)
{
	updateKeyFrameTime(frameTime);
	// drawSkeletonSmooth(g_timeAcc * m_keyFrameWalkCount);
}
