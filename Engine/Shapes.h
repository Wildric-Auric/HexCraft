#include "Globals.h"
//TODO::Pass vectors as references for all vertex structs
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

struct HexagonVertex {
	HexagonVertex(fVec3 position, float textureIndex);
	fVec3 position;
	float textureIndex;
};

struct HexaPrismVertex {
	HexaPrismVertex(const fVec3& position, const fVec2& uv, const fVec3& upVector,float textureIndex);
	fVec3 position;
	fVec2 uv;
	fVec3 upVector;
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

class Hexagon : public Shape {
private:
	uint32 VBO = 0;
	uint32 VAO = 0;
	uint32 EBO = 0;
public:
	static Hexagon instance;
	static uint32 indices[12];
	static HexagonVertex vertices[6];

	Hexagon() {};

	Hexagon(const HexagonVertex* const vert);

	void SetUpVerticesData(const HexagonVertex* const vert);
	void Draw()										     override;
	void Delete()										 override;
};


class HexaPrism : public Shape {
private:
	uint32 VBO = 0;
	uint32 VAO = 0;
	uint32 EBO = 0;
public:
	static HexaPrism instance;
	static uint32 indices[60];
	static HexaPrismVertex vertices[24];

	HexaPrism() {};

	HexaPrism(const HexaPrismVertex* const vert);

	void SetUpVerticesData(const HexaPrismVertex* const vert);
	void Draw()										     override;
	void Delete()										 override;

};