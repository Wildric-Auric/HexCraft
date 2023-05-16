#include "Shapes.h"
#include <glew.h>
#include <glfw3.h>



void Shapes::Init() {
	Quad::instance = Quad(nullptr);
}

void Shapes::Destroy() {
	Quad::instance.Delete();
}

Quad Quad::instance;


//uint8 Triangle::indices[3] = { 0, 1, 2 };

uint32 Quad::indices[6]	   = { 0, 1, 2, 1, 3, 2 };


Vertex::Vertex(fVec3 position, fVec2 uv) {
	this->position = position;
	this->uv       = uv;
}

Vertex Quad::vertices[4] = {
	Vertex({ -0.5, -0.5, 0.0}, {0.0, 0.0 }),
	Vertex({  0.5, -0.5, 0.0}, {1.0, 0.0 }),
	Vertex({ -0.5, 0.5, 0.0} , {0.0, 1.0 }),
	Vertex({  0.5, 0.5, 0.0} , {1.0, 1.0 })
};

#include <iostream>
void Quad::SetUpVerticesData(const Vertex* const vert) {
	//Generate and bind
	glGenBuffers(1, &this->EBO);
	glGenBuffers(1, &this->VBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//Fill buffers
	glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Vertex), &(vert[0].position.x), GL_STATIC_DRAW);
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

void Quad::Init() {
	Quad::instance = Quad(nullptr);
}


void Quad::Draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->EBO = 0; this->VAO = 0; this->VBO = 0;
}




//void Triangle::Init() {
//
//}
//
//void Triangle::Delete() {
//	
//}

