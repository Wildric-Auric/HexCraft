//TODO::Change this abstraction so that units are CPU and GPU batched
#pragma once
#include "Globals.h"
#include "Shader.h"
#include "Texture.h"

class UnitHex {
public:
	UnitHex() {};
	UnitHex(Shader* shader, Texture* texture, const fVec3& position = fVec3());

	void Draw();
	fVec3 GetWorldCoordinates();

	Shader*  shader  = nullptr;
	Texture* texture = nullptr;
	//Size is in world coordinates
	fVec3   size   = fVec3(500.0f, 500.0f, 500.0f);
	//Position is in integer coordinates (0,0), (1,0,0) for example; not world pixel coordinates
	fVec3 position;
};