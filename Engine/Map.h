#pragma once
#include "Globals.h"
#include "UnitHex.h"

#include <deque>
#include <unordered_map>
#include <list>
#include <map>

#define HEX_CHUNK_SIZE_X 32
#define HEX_CHUNK_SIZE_Y 32

#define HEX_BLOCK_SIZE_X 500
#define HEX_BLOCK_SIZE_Y 500
#define HEX_BLOCK_SIZE_Z 500

//in chunks; goes from -X to X for both axis
#define HEX_VIEW_DISTANCE 1
//in seconds
#define HEX_CHUNK_UNLOAD_TIME 5


//Chunks are allocated dynamically
class Chunck {
public:
	bool __shouldDraw = 1;
	Chunck() {};
	Chunck(const fVec2& position, float maxHeight = 5.0f, float minHeight = 5.0);

	fVec2 position = fVec2(0.0, 0.0);
	float maxHeight = 1.0;
	float minHeight = 1.0;

	std::deque<UnitHex> container;

	void Draw();
	void Delete(); 
	~Chunck(); //fuck this
};

//Maps should be allocated dynamically
class Map {
private: 
	bool __shouldDraw = 0;
public:

	Map() {};
	//TODO::Replace this by unordered map
	std::map<fVec2, Chunck*>  __chuncks;
	std::unordered_map<Chunck*, double> __timer;

	std::list<Chunck*> drawingOrder;
	
	float maxHeight = 60.0f;
	float minHeight = 1.0f;

	bool LoadChunk(  const fVec2&   position);
	bool UnloadChunk(const fVec2& position);
	void Update(const fVec3& playerPosition);

	//Map has only static draw
	void Draw();

	static UnitHex GenBlock(const fVec3& position, bool last = 0);
	static Map*    current;
};