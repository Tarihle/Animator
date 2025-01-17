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
	E_PALETTE,
	E_INTERPOLATEDPALETTE,
	E_INTERPOLATEDANIMS
};

class CustomSimulation : public ISimulation
{
	virtual void Init() override;
	virtual void Update(float frameTime) override;

	void drawWorldMarker();
	void drawLine(
		LM_::Vec3 const& pStart, LM_::Vec3 const& pEnd, LM_::Vec3 const& pColor,
		LM_::Vec3 const& pOffset = LM_::Vec3::zero()) const;

	std::vector<Transform> calculateTransforms(int animIndex, TransformType transformType, float lerpRatio = 0.f);
	std::vector<LM_::Mat4> calculateMatrices(int animIndex, TransformType transformType);
	std::vector<Transform> interpolateAnims(int anim1, int anim2, float frameTime);

	void drawSkeleton(int animIndex, TransformType transformType, float lerpRatio = 0.f);

	void updateKeyFrameTime(float frameTime);
	void updateKeyFrameTime(int animIndex, float frameTime);

	void step1(float frameTime);
	void step2(float frameTime);
	void step3(float frameTime);
	void step4(float frameTime);
	void step5(float frameTime);

	int					   m_playingAnim = 0;
	float				   m_globalTimeAcc = 0.f;
	float				   m_crossfadeTimeSpan = 0.5f;
	std::vector<Animation> m_Animations;
	Skeleton			   m_Skeleton;
};
