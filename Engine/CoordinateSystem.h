#pragma once
#include "Globals.h"


class CoordinateSystem {
public:
	static fVec3 WorldToHex(const fVec3& coord, const fVec3& unitSize);
	static fVec3 HexToWorld(const fVec3& coord, const fVec3& unitSize);

	static fVec2 WorldToChunck(const fVec3& worldCoord, const fVec3& hexUnitSize, const fVec2& chunkSize);
	static fVec2 HexToChunck(const fVec3& worldCoord, const fVec2& chunkSize);
	static fVec3 ChunkToHex(const fVec2& chunkCoord, const fVec2& chunkSize);

	static fVec3 WorldToRect(const fVec3& coord, const fVec3& unitSize);
	static fVec3 RectToWorld(const fVec3& coord, const fVec3& unitSize);
};