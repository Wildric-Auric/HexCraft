#pragma once
#include "Globals.h"
#include "Object.h"

#include <unordered_map>
#include <vector>


#define HEX_BATCH_MAX_VERTICES 21600000 // 9 float * 24 vertices; 10000 object ~10mb
#define HEX_BATCH_MAX_INDICES  6000000  // 10000 object each having 60 indices;

#define HEX_BATCH_SPARE_VERTICES 100
#define HEX_BATCH_SPARE_INDICES  100

//Batches are allocated dynamically; all elements of same batch have the SAME shader
//When maximal primitives per batch is reached or maximal textures are bound, a new batch is created

struct BatchInfo {
	void*  batchPtr = nullptr;
	uint32 offset   = 0;
	BatchInfo(void* batchPtr, uint32 offset) { this->batchPtr = batchPtr; this->offset = offset; }
};

struct IndexData {
	uint32* ptr  = nullptr;
	uint32  size = 0;
	IndexData(uint32* ptr, uint32 size) {this->ptr = ptr; this->size = size;}
};

struct VertexData {
	float* ptr  = nullptr;
	uint32 size = 0;
	VertexData(float* ptr,  uint32 size) {this->ptr = ptr; this->size = size;}
};

class Batch {
private:
	uint32 VAO;
	uint32 VBO;
		uint32 EBO;

	uint16  __currentTexSlot      = 0;
	uint32  __indicesOffset       = 0;
	uint32  __verticesOffset      = 0;
	bool    __isFull              = 0;
	//If set on 1 batch will clear next frame
	bool    __shouldClear		     = 0;
	bool    __shouldUpdateBuffers    = 0;
	bool    __shouldUpdateCPUBuffers = 0;

public:

	//Should be queried from opengl
	static uint16 maxTextures; 
	static std::unordered_map<Shader*, std::vector<Batch*>> batchMap;
	static std::unordered_map<Object*, BatchInfo>           batchLocation;
	static uint16 strideByteSize;
	static uint16 strideSize;
		
	static void Add(Object* obj, const VertexData& vertices, const IndexData& indices, void* modelMatrix = nullptr);
	//Force update in batch where obj is found
	static bool ForceUpdate(Object* obj);
	static void Clear(Object* obj);
	static void Remove(Object* obj);
	static void Update();
	static void DrawAll();

	float*  vertices = nullptr;
	uint32* indices  = nullptr;
	

	std::unordered_map<Texture*, uint32> textureMap;
	Shader* shader   = nullptr;
	
	void __Update();
	void Draw();	
	void __Clear();
	void __Remove();
	void BindTextures();
	void UpdateCPUBuff();
	void Delete();
	void ForceUpdate();
	//returns 1 on success and 0 on failure. Failure occur only if maximum texture slots has been reached
	bool __Add(Object* obj, const VertexData& vertices, const IndexData& indices, void* modelMatrix = nullptr);
	Batch();
	~Batch();
};