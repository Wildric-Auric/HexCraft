#include "Shapes.h"
#include <glew.h>
#include <glfw3.h>



void Shape::Init() {
	Quad::instance	   = Quad(nullptr);
	Triangle::instance = Triangle(nullptr);
	Cube::instance     = Cube(nullptr);
}

void Shape::Destroy() {
	Quad::instance.Delete();
	Triangle::instance.Delete();
}

Vertex::Vertex(fVec3 position, fVec2 uv) {
	this->position = position;
	this->uv       = uv;
}

CubeVertex::CubeVertex(fVec3 position, fVec2 uv, float textureIndex) {
	this->position	   = position;
	this->uv		   = uv;
	this->textureIndex = textureIndex;
}

//Quad----------------------------------------

Quad Quad::instance;
uint32 Quad::indices[6]	   = { 0, 1, 2, 1, 3, 2 };
Vertex Quad::vertices[4] = {
	Vertex({ -0.5, -0.5, 0.0}, {0.0, 0.0 }),
	Vertex({  0.5, -0.5, 0.0}, {1.0, 0.0 }),
	Vertex({ -0.5, 0.5, 0.0} , {0.0, 1.0 }),
	Vertex({  0.5, 0.5, 0.0} , {1.0, 1.0 })
};

void Quad::SetUpVerticesData(const Vertex* const vert) {
	//Generate and bind
	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//Fill buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(Quad::vertices), &(vert[0].position.x), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Quad::indices), Quad::indices, GL_STATIC_DRAW);
	//Enable attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0); //POSITION attrib

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vertex::position));
	glEnableVertexAttribArray(1); //UV attrib
	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Quad::Quad(const Vertex* const vert) {
	if (vert == nullptr) {
		SetUpVerticesData(Quad::vertices);
		return;
	}
	SetUpVerticesData(vert);
}

void Quad::Draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, sizeof(Quad::indices) / sizeof(Quad::indices[0]), GL_UNSIGNED_INT, 0);
}

void Quad::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->EBO = 0; this->VAO = 0; this->VBO = 0;
}

//Triangle---------------------------

Triangle Triangle::instance;
uint32 Triangle::indices[3]  = { 0, 1, 2 };
Vertex Triangle::vertices[3] = {
	Vertex({ -0.5, -0.5, 0.0 },{ 0.0, 0.0 }),
	Vertex({ 0.5, -0.5, 0.0 }, { 1.0, 0.0 }),
	Vertex({ -0.5, 0.5, 0.0 }, { 0.0, 1.0 })
};

Triangle::Triangle(const Vertex* const vert) {
	if (vert == nullptr) {
		SetUpVerticesData(Triangle::vertices);
		return;
	}
	SetUpVerticesData(vert);
}

void Triangle::SetUpVerticesData(const Vertex* const vert) {
	
	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	
	glBufferData(GL_ARRAY_BUFFER		, sizeof(Triangle::vertices), &(vert[0].position.x), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Triangle::indices) , Triangle::indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0); 

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vertex::position));
	glEnableVertexAttribArray(1); 
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Triangle::Draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, sizeof(Triangle::indices) / sizeof(Triangle::indices[0]), GL_UNSIGNED_INT, 0);
}

void Triangle::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->EBO = 0; this->VAO = 0; this->VBO = 0;
}

//Cube------------------------------------------

Cube Cube::instance;
uint32 Cube::indices[36] = { 
	0, 1, 2, 1, 3, 2,     //Front face
	4, 6, 3, 3, 1, 4,     //Right face
	4, 5, 6, 5, 7, 6,	  //Back face
	0, 2, 5, 5, 2, 7,     //Left face
	8, 10,9, 9, 10,3,     //Upper face
	0,12,11,11,12,13      //Lower face
};
CubeVertex Cube::vertices[14] = {
	//Front face
	CubeVertex({ -0.5, -0.5 , 0.5 }, { 0.0, 0.0 }, 0),
	CubeVertex({  0.5, -0.5 , 0.5 }, { 1.0, 0.0 }, 0),
	CubeVertex({ -0.5,  0.5 , 0.5 }, { 0.0, 1.0 }, 0),
	CubeVertex({  0.5,  0.5,  0.5 }, { 1.0, 1.0 }, 0),
	//Back face
	CubeVertex({   0.5, -0.5 , -0.5 }, { 0.0, 0.0 }, 0),
	CubeVertex({  -0.5, -0.5 , -0.5 }, { 1.0, 0.0 }, 0),
	CubeVertex({   0.5,  0.5 , -0.5 }, { 0.0, 1.0 }, 0),
	CubeVertex({  -0.5,  0.5 , -0.5 }, { 1.0, 1.0 }, 0),
	//Upper face
	CubeVertex({  -0.5,  0.5 , -0.5 }, { 0.0, 0.0 }, 0),
	CubeVertex({   0.5,  0.5 , -0.5 }, { 1.0, 0.0 }, 0),
	CubeVertex({  -0.5,  0.5 ,  0.5 }, { 0.0, 1.0 }, 0),
	//Lower face
	CubeVertex({   0.5,  -0.5 , 0.5 }, { 1.0, 0.0 }, 0),
	CubeVertex({  -0.5,  -0.5 , -0.5 },{ 0.0, 1.0 }, 0),
	CubeVertex({   0.5,  -0.5 , -0.5 },{ 1.0, 1.0 }, 0),

};

Cube::Cube(const CubeVertex* const vert) {
	if (vert == nullptr) {
		SetUpVerticesData(Cube::vertices);
		return;
	}
	SetUpVerticesData(vert);
}

void Cube::SetUpVerticesData(const CubeVertex* const vert) {

	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	glBufferData(GL_ARRAY_BUFFER,		  sizeof(Cube::vertices), &(vert[0].position.x), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Cube::indices) ,  Cube::indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CubeVertex), (void*)sizeof(CubeVertex::position));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Cube::Draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, sizeof(Cube::indices) / sizeof(Cube::indices[0]), GL_UNSIGNED_INT, 0);
}

void Cube::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->EBO = 0; this->VAO = 0; this->VBO = 0;
}


