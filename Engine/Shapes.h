#include "Globals.h"





class Shapes {
public:
	static void Init();
	static void Destroy();
};






struct Vertex {
	Vertex(fVec3 position, fVec2 uv);
	fVec3 position;
	fVec2 uv;
};

//class Triangle {
//private:
//	uint32 VBO, VAO, EBO = 0;
//public:
//	static Triangle instance;
//	static uint8 indices[3];
//
//	static void Init();
//	Triangle() {};
//	Triangle(iVec2 size);
//
//	iVec2 size;
//	Vertex vertices[3];
//	void Delete();
//};

class Quad {
private: 
	uint32 VBO = 0;
	uint32 VAO = 0;
	uint32 EBO = 0;
public:
	static Quad  instance;
	static uint32 indices[6];
	static void Init();
	static Vertex vertices[4];

	void SetUpVerticesData(const Vertex* const vert);

	Quad() {};
	//Default constructor: A quad of 1 unit size centered on screen if vert = nullptr
	Quad(const Vertex* const vert);
	void Draw();
	void Delete();
};