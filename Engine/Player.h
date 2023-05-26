#pragma once
#include "Globals.h"

class Player {
	fVec3 position;
	fVec2 rotation;

	fVec2 speed        = fVec2(5000.0f, 5000.0f);
	fVec2 sensitivty   = fVec2(5.0, 5.0);
	float acceleration = 3.0;
	float rotAcc       = 3.0;

	void Start();
	void Update();
};