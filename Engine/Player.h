#pragma once
#include "Globals.h"

class Player {
public:
	fVec3 position;
	fVec2 rotation;

	fVec2 speed        = fVec2(500.0, 500.0f);
	fVec2 sensitivty   = fVec2(5.0, 5.0);
	float acceleration = 3.0;
	float rotAcc       = 3.0;

	void Start();
	void Update();
};