#include "CoordinateSystem.h"

fVec3 CoordinateSystem::HexToWorld(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = coord.x * unitSize.x * 0.75;
	ret.y = coord.y * unitSize.y;
	ret.z = coord.z * unitSize.z + ( (int(coord.x) % 2 != 0) ? unitSize.z * 0.5 : 0.0);
	return ret;
}

fVec3 CoordinateSystem::WorldToHex(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = (4.0f / 3.0f) * (1.0 / unitSize.x) * coord.x;
	ret.y = (1.0f / unitSize.y) * coord.y;
	//ret.z = (1.0f / unitSize.z)				   * (coord.z - (int(ret.x) % 2 != 0 ? 0.5 : 0.0));
	ret.z = (1.0f / unitSize.z) * (coord.z - ((int(ret.x) % 2 != 0) ? unitSize.z * 0.5 : 0.0));

	return Maths::Floor(ret);

}


fVec2 CoordinateSystem::HexToChunck(const fVec3& hexCoord, const fVec2& chunkSize) {
	int x = 0;
	int y = 0;
	if (abs(hexCoord.x) > 0.01)
		x = hexCoord.x / chunkSize.x;
	if (abs(hexCoord.z) > 0.01)
		y = hexCoord.z / chunkSize.y;
	if (hexCoord.x < 0.0) 
		x -= 1;
	if (hexCoord.z < 0.0) 
		y -= 1;
	return fVec2(x,y);
}

fVec2 CoordinateSystem::WorldToChunck(const fVec3& worldCoord, const fVec3& hexUnitSize, const fVec2& chunkSize) {
	return CoordinateSystem::HexToChunck(CoordinateSystem::WorldToHex(worldCoord, hexUnitSize), chunkSize);
}

//Result is upper left block coordinate
fVec3 CoordinateSystem::ChunkToHex(const fVec2& chunkCoord, const fVec2& chunkSize) {
	return fVec3(chunkSize.x * chunkCoord.x, 0.0, chunkSize.y * chunkCoord.y);
}

fVec3 CoordinateSystem::WorldToRect(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = coord.x / unitSize.x;
	ret.y = coord.y / unitSize.y;
	ret.z = coord.z / unitSize.z;
	return ret;
}

fVec3 CoordinateSystem::RectToWorld(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = coord.x * unitSize.x;
	ret.y = coord.y * unitSize.y;
	ret.z = coord.z * unitSize.z;
	return ret;
}



