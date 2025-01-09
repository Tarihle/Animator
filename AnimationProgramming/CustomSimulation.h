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
};
