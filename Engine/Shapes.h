#include "Globals.h"

struct Vertex {
	Vertex(fVec3 position, fVec2 uv);
	fVec3 position;
	fVec2 uv;
};

struct CubeVertex {
	CubeVertex(fVec3 position, fVec2 uv, float textureIndex);
	fVec3 position;
	fVec2 uv;
	float textureIndex;
};

class Shape {
public:
	virtual void SetUpVerticesData(const Vertex* const vert) {};
	virtual void Draw()   {};
	virtual void Delete() {};

	static void Init();
	static void Destroy();
};


class Triangle : public Shape {
private:
	uint32 VBO = 0;
	uint32 VAO = 0;
	uint32 EBO = 0;
public:
	static Triangle instance;
	static uint32 indices[3];
	static Vertex vertices[3];

	Triangle() {};
	Triangle(const Vertex* const vert);

	void SetUpVerticesData(const Vertex* const vert) override;
	void Draw()										 override;
	void Delete()									 override;
};

class Quad : public Shape {
private: 
	uint32 VBO = 0;
	uint32 VAO = 0;
	uint32 EBO = 0;
public:
	static Quad  instance;
	static uint32 indices[6];
	static Vertex vertices[4];


	Quad() {};
	//Default constructor: A quad of 1 unit size centered on screen if vert = nullptr
	Quad(const Vertex* const vert);

	void SetUpVerticesData(const Vertex* const vert) override;
	void Draw()                                      override;
	void Delete()									 override;
};

class Cube : public Shape {
private:
	uint32 VBO = 0;
	uint32 VAO = 0;
	uint32 EBO = 0;
public:
	static Cube instance;
	static uint32 indices[36];
	static CubeVertex vertices[14];
	
	Cube() {};

	Cube(const CubeVertex* const vert);

	void SetUpVerticesData(const CubeVertex* const vert);
	void Draw()										     override;
	void Delete()										 override;
};