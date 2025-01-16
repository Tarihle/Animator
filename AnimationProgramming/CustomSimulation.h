#pragma once

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

#include "Animation.h"
#include "Bone.h"
#include "Skeleton.h"
#include "Transform.h"
#include "pch.h"

#include <vector>

enum class TransformType
{
	E_BINDPOSE,
	E_INVERSEBINDPOSE,
	E_PALETTE
};

class CustomSimulation : public ISimulation
{
	virtual void Init() override;
	virtual void Update(float frameTime) override;

	void drawWorldMarker();
	void drawLine(
		LM_::Vec3 const& pStart, LM_::Vec3 const& pEnd, LM_::Vec3 const& pColor,
		LM_::Vec3 const& pOffset = LM_::Vec3::zero()) const;

	std::vector<Transform> calculateTransforms(TransformType transformType);
	std::vector<Transform> calculateInterpolatedTransforms(float lerpRatio);
	std::vector<LM_::Mat4> calculateMatrices(TransformType transformType);

	void drawSkeletonstep1(void);
	void drawSkeleton(void);
	void drawSkeletonSmooth(float frameTime);

	void updateKeyFrameTime(float frameTime);

	void step1(float frameTime);
	void step2(float frameTime);
	void step3(float frameTime);
	void step4(float frameTime);
	void step5(float frameTime);

	// size_t				   m_boneCount;
	std::vector<Animation> m_Animations;
	Skeleton			   m_Skeleton;
	// std::vector<Bone>	   m_Bones;
	// std::vector<LM_::Mat4> m_inverseBindPoses;
};
