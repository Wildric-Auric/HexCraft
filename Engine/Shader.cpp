#include "Shader.h"
#include "Log.h"
#include <glew.h>
#include <glfw3.h>
#include <fstream>
ShaderString Shader::Parse(std::string path) { //For now it's just fragment and vertex shader
	ShaderString ret;
	ShaderType current = ShaderType::None;
	std::fstream file(path, std::ios_base::in);
	if (!file) {
		LOG_WARNING_FILE_CANNOT_OPEN(path);
		return ret;
	}
	for (std::string line; std::getline(file, line);) {
		if (line.find("//fragment shader") != -1)
			current = ShaderType::Fragment;
		else if (line.find("//vertex shader") != -1)   
			current = ShaderType::Vertex;
		if      (current == ShaderType::Fragment)      ret.fragment += line + '\n';
		else if (current == ShaderType::Vertex)		   ret.vertex   += line + '\n';
	}
	file.close();
	return ret;
}

int Shader::Compile(ShaderString shaderString) {
	//TODO::general log for every opengl function
	//Compiling vertex shader
	if (shaderString.vertex == "")
		return 0;
	const char* vertexSrc   = shaderString.vertex.c_str();
	const char* fragmentSrc = shaderString.fragment.c_str();
	
	uint32 vertexShader	  = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar* const*)&vertexSrc, NULL);
	glCompileShader(vertexShader);
	int successInfo = 0;
	char* log = new char[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successInfo);
	if (!successInfo) {
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		LOG("Error: Vertex Shader compilation failed");
		LOG("Path: " + this->path);
		LOG(std::string("Error details: "));
		delete[] log;
		return 0;
	}
	//Compiling fragment shader
	uint32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar* const*)&fragmentSrc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successInfo);
	if (!successInfo) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		LOG("Error: Fragment Shader compilation failed");
		LOG("Path: " + this->path);
		LOG(std::string("Error details: ") + log);
		delete[] log;
		return 0;
	}
	this->id = glCreateProgram();
	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragmentShader);
	glLinkProgram(this->id);
	glGetProgramiv(this->id, GL_LINK_STATUS, &successInfo);
	if (!successInfo) {
		glGetShaderInfoLog(this->id, 512, NULL, log);
		LOG("Error: Shader Link failed");
		LOG("Path: " + this->path);
		LOG(std::string("Error details: ") + log);
		delete[] log;
		this->id = 0;
		return 0;
	}
	//Clearing log allocated memory
	delete[] log;
	return 1;
}

int Shader::Recompile() {
	glDeleteProgram(this->id);
	this->id = 0;
	return Compile(Shader::Parse(this->path));
}

Shader::Shader(std::string path) {
	Shader::Compile(Shader::Parse(path));
}

void Shader::Use() {
	glUseProgram(this->id);
}

Shader::~Shader() {
	glDeleteProgram(this->id);
	this->id = 0;
}


