#pragma once

#include "stdafx.h"

#include "Engine.h"
#include "Simulation.h"

class CustomSimulation : public ISimulation
{
	virtual void Init() override;

	virtual void Update(float frameTime) override;
};
