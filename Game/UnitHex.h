//TODO::Change this abstraction so that units are CPU and GPU batched
#pragma once
#include "Globals.h"
#include "Object.h"



class UnitHex : public Object {
public:
	UnitHex() {};
	UnitHex(Shader* shader, Texture* texture, const fVec3& position = fVec3());
	
	//Will draw at corresponding member position
	void Draw()       override;
	Shader*  GetShader()  override;
	Texture* GetTexture() override;

	//Parameter in world Coordinates
	void Draw(const fVec3& worldPosition);


	Shader*  shader  = nullptr;
	Texture* texture = nullptr;
	//Size is in world coordinates
	fVec3   size   = fVec3(500.0f, 500.0f, 500.0f);
	//Position is in integer coordinates (0,0), (1,0,0) for example; not world pixel coordinates
	fVec3 position;
	bool  isBatched = 1;

	static std::unordered_map<std::string, UnitHex> blockTypes;
	static UnitHex* GetBlockType(std::string blockName);
	static void Init();
};