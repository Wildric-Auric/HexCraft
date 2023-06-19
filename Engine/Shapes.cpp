#include "Shapes.h"
#include <glew.h>
#include <glfw3.h>



void Shape::Init() {
	Quad::instance	   = Quad(nullptr);
	Triangle::instance = Triangle(nullptr);
	Cube::instance     = Cube(nullptr);
	Hexagon::instance  = Hexagon(nullptr);
	HexaPrism::instance= HexaPrism(nullptr);
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

HexagonVertex::HexagonVertex(fVec3 position, float textureIndex) {
	this->position     = position;
	this->textureIndex = textureIndex;
}

HexaPrismVertex::HexaPrismVertex(const fVec3& position, const fVec2& uv, const fVec3& up, float textureIndex) {
	this->position     = position;
	this->uv		   = uv;
	this->upVector     = up;
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

/*
					 7,8--------6,9	
					  /        /|	
					 /        / |	
				 2,10--------3  |	
					|        |  |	
					| 5,12     4,13	
					|        | /	
 					|        |/	
					0--------1,11
*/

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


//Hexagon-----------------------------------------------

Hexagon Hexagon::instance;
uint32 Hexagon::indices[12] = { 
	0, 1, 5,           //Left   triangle
	1, 2, 5, 2, 4, 5,  //Middle rectangle
	2, 3, 4			   //Right  triangle
};

HexagonVertex Hexagon::vertices[6] = {
	HexagonVertex({ -0.5,  0.0, 0.0},  0.0f),
	HexagonVertex({ -0.25, -0.5, 0.0}, 0.0f),
	HexagonVertex({  0.25, -0.5, 0.0}, 0.0f),
	HexagonVertex({  0.5,  0.0, 0.0}, 0.0f),
	HexagonVertex({  0.25, 0.5, 0.0}, 0.0f),
	HexagonVertex({ -0.25, 0.5, 0.0}, 0.0f)
};

void Hexagon::SetUpVerticesData(const HexagonVertex* const vert) {
	//Generate and bind
	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//Fill buffers
	glBufferData(GL_ARRAY_BUFFER,		  sizeof(Hexagon::vertices), &(vert[0].position.x), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Hexagon::indices), Hexagon::indices, GL_STATIC_DRAW);
	//Enable attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(HexagonVertex), (void*)0);
	glEnableVertexAttribArray(0); 

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(HexagonVertex), (void*)sizeof(HexagonVertex::position));
	glEnableVertexAttribArray(1); 
	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Hexagon::Hexagon(const HexagonVertex* const vert) {
	if (vert == nullptr) {
		SetUpVerticesData(Hexagon::vertices);
		return;
	}
	SetUpVerticesData(vert);
}

void Hexagon::Draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, sizeof(Hexagon::indices) / sizeof(Hexagon::indices[0]), GL_UNSIGNED_INT, 0);
}

void Hexagon::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->EBO = 0; this->VAO = 0; this->VBO = 0;
}

//HexaPrism----------------------------------------------

HexaPrism HexaPrism::instance;

uint32 HexaPrism::indices[60] = {
	//Lateral faces
	0, 1, 2, 1, 3, 2,
	1, 4, 3, 4, 5, 3,
	4, 6, 5, 6, 7, 5,
	6, 8, 7, 8, 9, 7,
	8, 10, 9, 10, 11, 9,
	10, 0, 11, 0, 2, 11,
	
	//Bases
	12, 13, 17, 
	13, 14, 17, 14, 16, 17,
	14,  15, 16,
	19,  18, 23,
	20,  19, 22, 19, 23, 22,
	22,  21, 20
};

static float xcos = std::cos(Maths::piDiv3);
static float xsin = std::sin(Maths::piDiv3);

static float ycos = std::cos(PI * 2.0 / 3.0);
static float ysin = std::sin(PI * 2.0 / 3.0);




HexaPrismVertex HexaPrism::vertices[24] = {
	HexaPrismVertex({ -0.25, -0.5, 0.5}, {0.0f, 0.0f}, {0.0, 1.0, 0.0}, 0.0f),
	HexaPrismVertex({  0.25, -0.5, 0.5}, {1.0f, 0.0f}, {0.0, 1.0, 0.0}, 0.0f),
	HexaPrismVertex({ -0.25,  0.5, 0.5}, {0.0f, 1.0f}, {0.0,-1.0, 0.0}, 0.0f),
	HexaPrismVertex({  0.25,  0.5, 0.5}, {1.0f, 1.0f}, {0.0,-1.0, 0.0}, 0.0f),
	HexaPrismVertex({  0.5,  -0.5, 0.0},  {0.0, 0.0} , {0.0, 1.0, 0.0}, 0.0f),
	HexaPrismVertex({  0.5,   0.5, 0.0},  {0.0, 1.0} , {0.0,-1.0, 0.0}, 0.0f),
	HexaPrismVertex({  0.25, -0.5, -0.5}, {1.0, 0.0} , {0.0, 1.0, 0.0}, 0.0f),
	HexaPrismVertex({  0.25,  0.5, -0.5}, {1.0, 1.0} , {0.0,-1.0, 0.0}, 0.0f),
	HexaPrismVertex({ -0.25, -0.5, -0.5}, {0.0, 0.0} , {0.0, 1.0, 0.0}, 0.0f),
	HexaPrismVertex({ -0.25,  0.5, -0.5}, {0.0, 1.0} , {0.0,-1.0, 0.0}, 0.0f),
	HexaPrismVertex({ -0.5,  -0.5,  0.0}, {1.0, 0.0} , {0.0, 1.0, 0.0}, 0.0f),
	HexaPrismVertex({ -0.5,   0.5,  0.0}, {1.0, 1.0} , {0.0,-1.0, 0.0}, 0.0f),
				
	HexaPrismVertex({ -0.5,    0.5,  0.0}, {0.0,  0.5} , {0.0, 1.0, 0.0}, 1.0f),
	HexaPrismVertex({ -0.25,   0.5,  0.5}, {0.25, 0.0} , {0.0, 1.0, 0.0}, 1.0f),
	HexaPrismVertex({  0.25,   0.5,  0.5}, {0.75, 0.0} , {0.0, 1.0, 0.0}, 1.0f),
	HexaPrismVertex({  0.5 ,   0.5,  0.0}, {1.0,  0.5} , {0.0, 1.0, 0.0}, 1.0f),
	HexaPrismVertex({  0.25,   0.5, -0.5}, {0.75, 1.0} , {0.0, 1.0, 0.0},1.0f),
	HexaPrismVertex({ -0.25 ,  0.5, -0.5}, {0.25, 1.0} , {0.0, 1.0, 0.0}  ,1.0f),

	HexaPrismVertex({ -0.5,    -0.5,  0.0}, {0.0,  0.5}   , {0.0, -1.0, 0.0}, 2.0f),
	HexaPrismVertex({ -0.25,   -0.5,  0.5}, {0.25, 0.0}   , {0.0, -1.0, 0.0}, 2.0f),
	HexaPrismVertex({  0.25,   -0.5,  0.5}, {0.75, 0.0}   , {0.0, -1.0, 0.0}, 2.0f),
	HexaPrismVertex({  0.5 ,   -0.5,  0.0}, {1.0,  0.5}   , {0.0, -1.0, 0.0}, 2.0f),
	HexaPrismVertex({  0.25,   -0.5, -0.5}, {0.75, 1.0}  , {0.0, -1.0, 0.0}, 2.0f),
	HexaPrismVertex({ -0.25 ,  -0.5, -0.5}, {0.25,  1.0}    , {0.0, -1.0, 0.0}, 2.0f)
};

void HexaPrism::SetUpVerticesData(const HexaPrismVertex* const vert) {
	//Generate and bind
	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//Fill buffers
	glBufferData(GL_ARRAY_BUFFER, sizeof(HexaPrism::vertices), &(vert[0].position.x), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(HexaPrism::indices), HexaPrism::indices, GL_STATIC_DRAW);
	//Enable attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(HexaPrismVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(HexaPrismVertex), (void*)(sizeof(HexaPrismVertex::position)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(HexaPrismVertex), (void*)(sizeof(HexaPrismVertex::position) + sizeof(HexaPrismVertex::uv)));
	glEnableVertexAttribArray(2);

	int size = sizeof(HexaPrismVertex::position) + sizeof(HexaPrismVertex::uv) + sizeof(HexaPrismVertex::upVector);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(HexaPrismVertex), (void*)(size));
	glEnableVertexAttribArray(3);
	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

HexaPrism::HexaPrism(const HexaPrismVertex* const vert) {
	if (vert == nullptr) {
		SetUpVerticesData(HexaPrism::vertices);
		return;
	}
	SetUpVerticesData(vert);
}

void HexaPrism::Draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, sizeof(HexaPrism::indices) / sizeof(HexaPrism::indices[0]), GL_UNSIGNED_INT, 0);
}

void HexaPrism::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->EBO = 0; this->VAO = 0; this->VBO = 0;
}
