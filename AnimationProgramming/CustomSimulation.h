#pragma once

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

#include "pch.h"

class CustomSimulation : public ISimulation
{
	virtual void Init() override;

	virtual void Update(float frameTime) override;

	void drawWorldMarker();

	void drawLine(
		LM_::Vec3 const& pStart, LM_::Vec3 const& pEnd, LM_::Vec3 const& pColor,
		LM_::Vec3 const& pOffset = LM_::Vec3::zero()) const;

	void drawSkeleton(int firstIndex, int lastIndex, LM_::Mat4 inverseBindMatrix);

	void step1(float frameTime);
	//void step2(float frameTime);
	//void step3(float frameTime);
	//void step4(float frameTime);
	//void step5(float frameTime);
};
