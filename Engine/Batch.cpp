#include "Batch.h"
#include "glew.h"
#include "Camera.h"	
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Log.h"

uint16 Batch::maxTextures    = 30; //Tmp
uint16 Batch::strideSize     = 9;
uint16 Batch::strideByteSize = 9 * sizeof(float);  //12 bytes ----> position; 8 bytes ----> uv; 12 bytes ----> up vector ; 1 byte ----> texture data
std::unordered_map <Shader*, std::vector<Batch*>> Batch::batchMap;
std::unordered_map<Object*, BatchInfo>            Batch::batchLocation;




void Batch::DrawAll() {
	for (const auto& iter : Batch::batchMap) {
		iter.first->Use();
		iter.first->SetUniform(GLSLDataType::Mat4f, "uVP", { &Camera::activeCam->VP[0][0] });

		for (Batch* batch : iter.second) {
			batch->Draw();
		}
	}
}

void Batch::Clear(Object* obj) {
	auto iter = Batch::batchLocation.find(obj);
	if (iter == Batch::batchLocation.end() || iter->second.batchPtr == nullptr)
		return;
	((Batch*)iter->second.batchPtr)->__Clear();
}

void Batch::Remove(Object* obj) {
	auto iter = Batch::batchLocation.find(obj);
	if (iter == Batch::batchLocation.end() || iter->second.batchPtr == nullptr)
		return;
	((Batch*)iter->second.batchPtr)->__Remove();
	Batch::batchLocation.erase(iter->first);
}

void Batch::__Remove() {
	this->__shouldUpdateCPUBuffers = 1;
	this->__shouldUpdateBuffers = 1;
}

void Batch::UpdateCPUBuff() {

	this->__indicesOffset = 0;
	this->__verticesOffset = 0;
	this->__isFull = 0;
	this->__currentTexSlot = 0;

	this->textureMap.clear();

	auto iter = batchLocation.begin();

	std::vector<Object*> objs;
	while (iter != batchLocation.end()) {
		if (iter->second.batchPtr == this) {
			objs.push_back(iter->first);
			iter = batchLocation.erase(iter);
			continue;
		}
		++iter;
	}

	for (Object* obj : objs) 
		obj->Draw();

	this->__shouldUpdateCPUBuffers = 0;
}

bool Batch::__Add(Object* obj, const VertexData& vertices, const IndexData& indices, void* modelMatrix) {

	auto texIter = textureMap.find(obj->GetTexture());

	if (texIter == textureMap.end()) {
		if (this->__currentTexSlot >= Batch::maxTextures) return 0;
		texIter = textureMap.insert(std::make_pair(obj->GetTexture(), ++this->__currentTexSlot)).first;
	}
	//Adds to batch location map
	BatchInfo bi{ (void*)this, __verticesOffset };
	Batch::batchLocation.insert(std::make_pair(obj, bi));
	//Adds vertices
	for (int i = 0; i < vertices.size; ++i) {
		float value  = *(vertices.ptr + i);
		//Computes Model * localPosition and insert it in vertices
		if ( ((i % Batch::strideSize) == 0) && (modelMatrix != nullptr) ) {
			glm::vec4 pos = *((glm::mat4*)(modelMatrix)) * glm::vec4( value, 
																   *(vertices.ptr + i + 1), 
																   *(vertices.ptr + i + 2),
																   1.0f);
			*(this->vertices + this->__verticesOffset + i)	   = pos.x;
			*(this->vertices + this->__verticesOffset + i + 1) = pos.y;
			*(this->vertices + this->__verticesOffset + i + 2) = pos.z;
			i+=2;
			continue;
		}

		if ( ( (i % Batch::strideSize) == 5) && (modelMatrix != nullptr) ) {
			glm::vec4 pos                                      = *((glm::mat4*)modelMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			*(this->vertices + this->__verticesOffset + i)	   = pos.x;
			*(this->vertices + this->__verticesOffset + i + 1) = pos.y;
			*(this->vertices + this->__verticesOffset + i + 2) = pos.z;
			i+=2;
			continue; //Fuck, this line was forgotten and caused lighting errors
		}

		if ( (i % Batch::strideSize) == Batch::strideSize - 1)
			value += 100 * (texIter->second);
		*(this->vertices + this->__verticesOffset + i) = value;
	}

	//Adds indices
	for (int i = 0; i < indices.size; ++i) {
		//TODO::fix magic numbers
		*(this->indices + this->__indicesOffset + i) = *(indices.ptr + i) + this->__verticesOffset / 9;
	}

	//Updates offsets
	this->__indicesOffset     +=  indices.size;
	this->__verticesOffset    +=  vertices.size;
	//Updates batch completion flag
	if (this->__verticesOffset >= HEX_BATCH_MAX_VERTICES || this->__indicesOffset >= HEX_BATCH_MAX_INDICES)
		this->__isFull = 1;
	
	this->__shouldUpdateBuffers = 0;
	return 1;
}

void Batch::ForceUpdate() {
	this->__shouldUpdateBuffers = 1;
}

bool Batch::ForceUpdate(Object* obj) {
	auto iter = Batch::batchLocation.find(obj);
	if (iter == Batch::batchLocation.end())
		return 0;
	((Batch*)iter->second.batchPtr)->ForceUpdate();
	return 1;
}

//TODO::Make this return a value that indicates how the vertices were added
void Batch::Add(Object* obj, const VertexData& vertices, const IndexData& indices, void* modelMatrix) {
	std::unordered_map<Shader*, std::vector<Batch*>>::iterator iter  = Batch::batchMap.find(obj->GetShader());
	
	//No batches for the shader
	if (iter == Batch::batchMap.end()) {
		std::vector<Batch*> vec = { new Batch};
		iter = Batch::batchMap.insert(std::make_pair(obj->GetShader(), vec)).first;
		iter->second.back()->shader = obj->GetShader();
		
		iter->second.back()->__shouldUpdateBuffers = 1;
	}
	//if already there, we don't add the object render
	auto iter0 = Batch::batchLocation.find(obj);
	if (iter0 != Batch::batchLocation.end()) {
		return;
	};
	//Find an available batch slot
	for (const auto& batch : iter->second) {
		if (batch->__isFull || !batch->__Add(obj, vertices, indices, modelMatrix)) {
			continue;
		}
		//Add the the stide
		batch->__shouldUpdateBuffers = 1;
		return;
	}
	//Add new batch if all batches are full
	iter->second.push_back(new Batch);
	iter->second.back()->shader = obj->GetShader();
	iter->second.back()->__Add(obj, vertices, indices, modelMatrix);
	iter->second.back()->__shouldUpdateBuffers = 1;
};

void Batch::__Clear() {
	this->__indicesOffset  = 0;
	this->__verticesOffset = 0;
	this->__isFull         = 0;
	this->__currentTexSlot = 0;

	this->textureMap.clear();

	auto iter = batchLocation.begin();
	while ( iter != batchLocation.end() ) {
		if (iter->second.batchPtr == this) {
			iter = batchLocation.erase(iter);
			continue;
		}
		++iter;
	}

	this->__shouldClear         = 0;
	this->__shouldUpdateBuffers = 1;
}


void Batch::Update() {
	for (const auto& iter : batchMap) {
		for (Batch* batch : iter.second) {
			if (batch->__shouldUpdateCPUBuffers)
				batch->UpdateCPUBuff();
			if (batch->__shouldUpdateBuffers)
				batch->__Update();
			if (batch->__shouldClear)
				batch->__Clear();
		}
	}
}

void Batch::__Update() {
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	//Should I bind element array buffer manually?
	//Thank you mr.comment
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->__verticesOffset * sizeof(float), this->vertices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->__indicesOffset * sizeof(uint32), this->indices);

	this->__shouldUpdateBuffers = 0;
	glBindVertexArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Batch::BindTextures() {
	int i = 1;
	for (const auto& iter : textureMap) {
		iter.first->Bind(iter.second);
	}	
}

Batch::Batch() {
	//Initialize VBO, EBO abd VAO
	glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER,		  this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	uint32 constexpr byteSizeVert = (HEX_BATCH_MAX_VERTICES + HEX_BATCH_SPARE_VERTICES) * sizeof(float);
	uint32 constexpr byteSizeInd  = (HEX_BATCH_MAX_INDICES  + HEX_BATCH_SPARE_INDICES ) * sizeof(uint32);

	glBufferData(GL_ARRAY_BUFFER,		  byteSizeVert, nullptr,        GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSizeInd, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Batch::strideByteSize, (const void*)0);  // position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, Batch::strideByteSize, (const void*)12); // uv
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, Batch::strideByteSize, (const void*)20); // up vector
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, Batch::strideByteSize, (const void*)32); // texture
	glEnableVertexAttribArray(3);
	//------------------
	this->vertices = new float[HEX_BATCH_MAX_VERTICES  + HEX_BATCH_SPARE_VERTICES];
	this->indices  = new uint32[HEX_BATCH_MAX_INDICES  + HEX_BATCH_SPARE_INDICES];
}

void Batch::Draw() {
	glBindVertexArray(this->VAO);
	this->BindTextures();
	int arr[33];
	arr[0] = 32;
	for (int i = 1; i < 33; ++i) { arr[i] = i; }
	this->shader->SetUniform(GLSLDataType::IntegerArray, "uTex", arr);

	glDrawElements(GL_TRIANGLES, this->__indicesOffset * sizeof(this->indices[0]), GL_UNSIGNED_INT, 0);
}

void Batch::Delete() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	this->VAO = 0;
	this->VBO = 0;
	this->EBO = 0;
}

Batch::~Batch() {
	this->Delete();
	delete[] this->vertices;
	delete[] this->indices;
	this->__indicesOffset  = 0;
	this->__verticesOffset = 0;
}