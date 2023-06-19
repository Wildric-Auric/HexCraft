#include "Map.h"
#include "Noise.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourcesManager.h"
#include "FPS.h"
#include "Batch.h"
#include "CoordinateSystem.h"

#include "imgui/imgui.h"

Map* Map::current;


//TODO::Various blocks generation
UnitHex Map::GenBlock(const fVec3& position) {
	UnitHex grassBlock  = *UnitHex::GetBlockType("Grass");
	grassBlock.position = position;
	return grassBlock;
}

Chunck::Chunck(const fVec2& position, float maxHeight, float minHeight) {
	this->position  = position;
	this->maxHeight = maxHeight;
	this->minHeight=  minHeight;
	//For now we call noise function
	fVec3 chunkOffset = CoordinateSystem::ChunkToHex(position, fVec2(HEX_CHUNK_SIZE_X,HEX_CHUNK_SIZE_Y));

	for (int x = chunkOffset.x; x < HEX_CHUNK_SIZE_X + chunkOffset.x; ++x) {
		for (int z = chunkOffset.z; z < HEX_CHUNK_SIZE_Y + chunkOffset.z; ++z) {
			int yy = Maths::Max<float>(this->maxHeight * Noise::ValueNoise(fVec2(x,z) * (1.0f / 100.0f)), this->minHeight);
			//ChunkToHex.Y is always 0.0, fVec3 is used only for convention
			for (int y = chunkOffset.y; y < yy + chunkOffset.y; y++) {
				UnitHex temp = Map::GenBlock(fVec3(x, y, z));
				this->container.push_back(temp);
			}
		}
	}
}

void Chunck::Draw() {
	//Update delete objs from batch
	if (!this->__shouldDraw) return;
	for (UnitHex& block : this->container) {
		block.Draw();	
	}
}


void Chunck::Delete() {

}

Chunck::~Chunck() {
	for (UnitHex& hex : this->container) {
		Batch::Remove(&hex);
	}
}


bool Map::LoadChunk(const fVec2& position) {
	auto iter = this->__chuncks.find(position);
	//Already there
	if (iter != this->__chuncks.end()) {
		this->__timer.erase(iter->second);
		return 0;
	}
	//Adding new chunk
    Chunck* chunck = new Chunck(position, this->maxHeight, this->minHeight);
	iter = this->__chuncks.insert(std::make_pair(position, chunck)).first;
	this->__timer.erase(iter->second);
	this->__shouldDraw   = 1;
	chunck->__shouldDraw = 1;
	return 1;
}


bool Map::UnloadChunk(const fVec2& position) {
	auto iter = this->__chuncks.find(position);
	if (iter == this->__chuncks.end()) 
		return 0;
	auto iter0 = this->__timer.find(iter->second);
	if (iter0 != this->__timer.end())
		return 1;
	this->__timer.insert(std::make_pair(iter->second, HEX_CHUNK_UNLOAD_TIME));
}

void Map::Update(const fVec3& playerPosition) {
	//Delete what should be deleted
	auto iter = this->__timer.begin();
	while (iter != this->__timer.end()) { 
		iter->second -= FPS::deltaTime; 
		if (iter->second > 0.0) {
			++iter;
			continue;
		}
		this->__shouldDraw		  = 1;
		iter->first->__shouldDraw = 1;
		this->__chuncks.erase(iter->first->position);	
		Chunck* cPtr = (&*iter->first);
		iter = this->__timer.erase(iter);
		//Deleting the chunk
		delete cPtr;
	}

	//Load Neighbour chuncks
	fVec2 coord = CoordinateSystem::WorldToChunck(playerPosition, fVec3(HEX_BLOCK_SIZE_X, HEX_BLOCK_SIZE_Y, HEX_BLOCK_SIZE_Z), fVec2(HEX_CHUNK_SIZE_X, HEX_CHUNK_SIZE_Y));
	ImGui::Begin("Test");
	ImGui::DragFloat2("COORDTEST", &coord.x);
	ImGui::End();

	for (auto& iter0 : this->__chuncks) {
		fVec2 diff = fVec2(std::abs(coord.x - iter0.second->position.x), std::abs(coord.y - iter0.second->position.y));
		//TODO::Replace magic value<<
		if (diff.x > 1 || diff.y > 1)
			this->UnloadChunk(iter0.second->position);
	}

	this->LoadChunk(fVec2(coord.x, coord.y));
	this->LoadChunk(fVec2(coord.x + 1, coord.y));
	this->LoadChunk(fVec2(coord.x + 1, coord.y + 1));
	this->LoadChunk(fVec2(coord.x, coord.y + 1));
	this->LoadChunk(fVec2(coord.x - 1, coord.y + 1));
	this->LoadChunk(fVec2(coord.x - 1, coord.y));
	this->LoadChunk(fVec2(coord.x - 1, coord.y - 1));
	this->LoadChunk(fVec2(coord.x, coord.y - 1));
	this->LoadChunk(fVec2(coord.x + 1, coord.y - 1));
}

void Map::Draw() {
	if (!this->__shouldDraw) return;
	this->__shouldDraw = 0;
	for (auto& pair : this->__chuncks) {
		pair.second->Draw();
	}
}

