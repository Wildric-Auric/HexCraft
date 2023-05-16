#pragma once
#include <string>
#include "Globals.h"
#include "Maths.h"

enum ShaderType {
	None,
	Vertex,
	Fragment
};

struct ShaderString {
	std::string vertex   = "";
	std::string fragment = "";
};

class Shader {
public:
	uint32 id		 = 0;
	std::string path = "";
	Shader() {};
	Shader(std::string path);
	int  Compile(ShaderString shaderString);
	int  Recompile(); //Note that it deletes the version old shader; if there is error in the new code the shader is empty
	void Use();
	~Shader();

	static ShaderString Parse(std::string path);
};