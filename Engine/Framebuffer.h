#pragma once
#include "Globals.h"
#include "Texture.h"

//We will use this for post processing among other stuff

class FrameBuffer {
private:
	uint32 frameBufferId;
	uint32 renderBufferId;

public:
	FrameBuffer() {};
	FrameBuffer(const iVec2& size);
	
	Texture renderTex;

	void Bind();
	void Unbind();
	void Delete();

};