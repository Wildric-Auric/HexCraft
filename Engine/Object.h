#pragma once

#include "Texture.h"
#include "Shader.h"

class Object {
public:
	Object() {}
	Texture* tex      = nullptr;
	Shader*  shader   = nullptr;

	virtual void Draw()       {};
	virtual Shader*  GetShader()  {return nullptr;}
	virtual Texture* GetTexture() {return nullptr;}
};