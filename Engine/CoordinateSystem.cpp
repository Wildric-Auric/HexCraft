#include "CoordinateSystem.h"

fVec3 CoordinateSystem::HexToWorld(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = coord.x * unitSize.x * 0.75;
	ret.y = coord.y * unitSize.y;
	ret.z = coord.z * unitSize.z + ( (int(coord.x) % 2 != 0) ? unitSize.z * 0.5 : 0.0);
	return ret;
}

fVec3 CoordinateSystem::WorldToHex(const fVec3& c, const fVec3& unitSize) {
	fVec2 halfSize = fVec2(unitSize.x, unitSize.y) * 0.5;
	float yCoord         = c.y / unitSize.y;
	//Center on 0,0
	fVec2 coord = fVec2(c.x + halfSize.x, c.y + halfSize.y);
	fVec2 absoluteSign  = fVec2(Maths::Sign(coord.x), Maths::Sign(coord.y));
	//Operations to get location given coord.x
	float fractPart = fmod(coord.x, 3.0 * halfSize.x);
	float intPart   = (float)((int)(coord.x / (3.0 * halfSize.x)));

	//The smaller rectangle
	if (fractPart >= (2.0 * halfSize.x)) {
		return fVec3(2.0 * intPart + 1.0, yCoord, coord.y / halfSize.y);
	}
	//The widder rectangle
	fVec3 ret      = fVec3(2.0 * intPart, yCoord, (int)(coord.y * 0.5 / halfSize.y));
	fVec2 rectPos  = fVec2(3.0 * intPart * halfSize.x + absoluteSign.x * halfSize.x, 
						   ret.y * 2.0 * halfSize.y + absoluteSign.y * halfSize.y);
	fVec2 localPos = coord - rectPos;
	//Restriction to upper right quarter of the rectangle
	fVec2 localPosRest  = fVec2(abs(localPos.x), abs(localPos.y));
	fVec2 localSign     = fVec2(Maths::Sign(localPos.x), Maths::Sign(localPos.y));
	
	fVec3 recSideVec    = fVec3(fVec2(0.5 * halfSize.x, halfSize.y), 0.0  , 0.0);



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



