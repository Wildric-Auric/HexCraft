#pragma once
#include <string>
#include "Globals.h"
#include "Maths.h"

enum ShaderType {
	None,
	VertexShader,
	FragmentShader,
};

enum GLSLDataType {
	Float,
	Integer,
	Float2,
	Integer2,
	Float3,
	Integer3,
	Mat4f
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
	//Data is an array to values of uniform. If datatype is Integer3 then data contains three elements of datatype int, programmer should be sure of size
		void SetUniform(GLSLDataType datatype, const char* uniformName, void* data);
	ShaderString Parse(std::string path);
	int  Compile(ShaderString shaderString);
	int  Recompile(); //Note that it deletes the version old shader; if there is error in the new code the shader is empty
	void Use();
	~Shader();

};