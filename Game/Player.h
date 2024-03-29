#pragma once
#include "Globals.h"

class Player {
public:
	fVec3 position;
	fVec2 rotation = fVec2(0.0, - 45.0);

	fVec3 forward; //READ ONLY
	fVec2 speed        = fVec2(3000.0, 5000.0f);
	fVec2 sensitivty   = fVec2(30.0, 30.0);
	float acceleration = 3.0;
	float rotAcc       = 3.0;

	void Start();
	void Update();
};