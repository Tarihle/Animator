#include "CustomSimulation.h"

LM_::Vec3 g_Origin(0.f);
LM_::Vec3 g_Red(1.f, 0.f, 0.f);
LM_::Vec3 g_Green(0.f, 1.f, 0.f);
LM_::Vec3 g_Blue(0.f, 0.f, 1.f);

float g_crossFade = 0.f;
float g_fps = 0.f;

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

	m_Skeleton.m_inverseBindPoses = calculateMatrices(0, TransformType::E_INVERSEBINDPOSE);

	m_globalTimeAcc = 0.5f + (rand() / (RAND_MAX / (5.5f - 0.5f))); // Random value between 0.5 and 5.5 seconds
																	// std::cout << g_randomTime << std::endl;
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
	// step4(frameTime);
	step5(frameTime);
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

std::vector<Transform> CustomSimulation::calculateTransforms(int animIndex, TransformType transformType, float lerpRatio)
{
	std::vector<Transform> bones(m_Skeleton.m_boneCount);

	for (int index = 0; index < bones.size(); index++)
	{
		bones[index] = m_Skeleton.m_Bones[index].m_localTransform;

		if (transformType == TransformType::E_PALETTE)
		{
			bones[index] = m_Animations[0].m_animFrameTransforms[m_Animations[animIndex].m_keyFrame][index] * bones[index];
		}
		else if (transformType == TransformType::E_INTERPOLATEDPALETTE)
		{
			int		  nextKeyFrame = (m_Animations[animIndex].m_keyFrame + 1) % m_Animations[animIndex].m_keyFrameCount;
			Transform currentFrameBone =
				m_Animations[animIndex].m_animFrameTransforms[m_Animations[animIndex].m_keyFrame][index] * bones[index];
			Transform nextFrameBone = m_Animations[animIndex].m_animFrameTransforms[nextKeyFrame][index] * bones[index];
			bones[index] = interpolate(currentFrameBone, nextFrameBone, lerpRatio);
		}
		else if (transformType == TransformType::E_INTERPOLATEDANIMS)
		{
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

std::vector<LM_::Mat4> CustomSimulation::calculateMatrices(int animIndex, TransformType transformType)
{
	std::vector<Transform> bones = calculateTransforms(animIndex, transformType);
	std::vector<LM_::Mat4> matrices(bones.size());

	for (int index = 0; index < bones.size(); index++)
	{
		matrices[index] = bones[index];
	}

	return matrices;
}

std::vector<Transform> CustomSimulation::interpolateAnims(int anim1, int anim2, float frameTime)
{
	if (g_crossFade == 0.f)
	{
		float pourcentage = (m_Animations[m_playingAnim].m_keyFrame + frameTime) / m_Animations[m_playingAnim].m_keyFrameCount;
		float frame = m_Animations[anim2].m_keyFrameCount * pourcentage;

		m_Animations[anim2].m_keyFrame = int(frame);
		m_Animations[anim2].m_timeAcc = frame - int(frame);
	}

	updateKeyFrameTime(anim2, frameTime);
	g_crossFade += frameTime;

	std::vector<Transform> bonesPalette1 = calculateTransforms(
		anim1, TransformType::E_INTERPOLATEDPALETTE, m_Animations[anim1].m_timeAcc * m_Animations[anim1].m_keyFrameCount);

	std::vector<Transform> bonesPalette2 = calculateTransforms(
		anim2, TransformType::E_INTERPOLATEDPALETTE, m_Animations[anim2].m_timeAcc * m_Animations[anim2].m_keyFrameCount);

	std::vector<Transform> interpolated(bonesPalette1.size());
	for (int i = 0; i < bonesPalette1.size(); i++)
	{
		interpolated[i] = interpolate(bonesPalette1[i], bonesPalette2[i], g_crossFade / m_crossfadeTimeSpan); //* 2 = / 0.5f
	}

	return interpolated;
}

void CustomSimulation::drawSkeleton(int animIndex, TransformType transformType, float lerpRatio)
{
	std::vector<Transform> bones = calculateTransforms(animIndex, transformType, lerpRatio);

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
	if (m_Animations[m_playingAnim].m_timeAcc < (1.f / 30))
	{
		m_Animations[m_playingAnim].m_timeAcc += frameTime;
		g_fps += 1.f;
	}
	else if (m_Animations[m_playingAnim].m_keyFrame < m_Animations[m_playingAnim].m_keyFrameCount - 1)
	{
		m_Animations[m_playingAnim].m_timeAcc = 0.f;
		++m_Animations[m_playingAnim].m_keyFrame;
		g_fps += 1.f + 0.01f;
	}
	else
	{
		m_Animations[m_playingAnim].m_timeAcc = 0.f;
		m_Animations[m_playingAnim].m_keyFrame = 0;
		g_fps += 1.f + 0.01f;
	}

	if ((g_fps - int(g_fps)) >= 0.3f)
	{
		std::cout << "FPS = " << int(g_fps) << std::endl;
		g_fps = 0.f;
	}

	m_globalTimeAcc -= frameTime;
}

void CustomSimulation::updateKeyFrameTime(int animIndex, float frameTime)
{
	if (m_Animations[animIndex].m_timeAcc < (1.f / 30))
	{
		m_Animations[animIndex].m_timeAcc += frameTime;
	}
	else if (m_Animations[animIndex].m_keyFrame < m_Animations[animIndex].m_keyFrameCount - 1)
	{
		m_Animations[animIndex].m_timeAcc = 0.f;
		++m_Animations[animIndex].m_keyFrame;
	}
	else
	{
		m_Animations[animIndex].m_timeAcc = 0.f;
		m_Animations[animIndex].m_keyFrame = 0;
	}
}

void CustomSimulation::step1(float frameTime)
{
	drawSkeleton(m_playingAnim, TransformType::E_BINDPOSE);
}

void CustomSimulation::step2(float frameTime)
{
	updateKeyFrameTime(frameTime);

	drawSkeleton(m_playingAnim, TransformType::E_PALETTE);
}

void CustomSimulation::step3(float frameTime)
{
	updateKeyFrameTime(frameTime);

	drawSkeleton(m_playingAnim, TransformType::E_PALETTE);

	std::vector<LM_::Mat4> bonesPalette = calculateMatrices(m_playingAnim, TransformType::E_PALETTE);
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
	updateKeyFrameTime(m_playingAnim, frameTime);
	// updateKeyFrameTime(frameTime);

	drawSkeleton(0, TransformType::E_INTERPOLATEDPALETTE, m_Animations[0].m_timeAcc * m_Animations[0].m_keyFrameCount);

	std::vector<Transform> bonesPalette =
		calculateTransforms(0, TransformType::E_INTERPOLATEDPALETTE, m_Animations[0].m_timeAcc * m_Animations[0].m_keyFrameCount);
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
	if (m_globalTimeAcc <= -m_crossfadeTimeSpan)
	{
		m_playingAnim = (m_playingAnim == 0 ? 1 : 0);
		m_globalTimeAcc = 0.f;
		m_globalTimeAcc = 2.5f + (rand() / (RAND_MAX / (5.5f - 2.5f))); // Random value between 0.5 and 5.5 seconds
		m_Animations[(m_playingAnim == 0 ? 1 : 0)].m_timeAcc = 0.f;
		g_crossFade = 0.f;
	}
	updateKeyFrameTime(frameTime);

	std::vector<Transform> bonesPalette;
	if (m_globalTimeAcc <= 0.f && m_globalTimeAcc >= -m_crossfadeTimeSpan)
	{
		bonesPalette = (m_playingAnim == 0 ? interpolateAnims(0, 1, frameTime) : interpolateAnims(1, 0, frameTime));
	}
	else
	{
		bonesPalette = calculateTransforms(
			m_playingAnim, TransformType::E_INTERPOLATEDPALETTE,
			m_Animations[m_playingAnim].m_timeAcc * m_Animations[m_playingAnim].m_keyFrameCount);
	}

	std::vector<LM_::Mat4> skinMatrices;
	skinMatrices.reserve(m_Skeleton.m_inverseBindPoses.size());

	for (int i = 0; i < m_Skeleton.m_inverseBindPoses.size(); i++)
	{
		skinMatrices.push_back(LM_::Mat4(bonesPalette[i]) * m_Skeleton.m_inverseBindPoses[i]);
	}

	SetSkinningPose(&skinMatrices[0][0][0], skinMatrices.size());
}
