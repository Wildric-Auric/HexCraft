#include "CoordinateSystem.h"

fVec3 CoordinateSystem::HexToWorld(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = coord.x * unitSize.x * 0.75;
	ret.y = coord.y * unitSize.y;
	ret.z = coord.z * unitSize.z + ( (int(coord.x) % 2 != 0) ? unitSize.z * 0.5 : 0.0);
	return ret;
}

fVec3 CoordinateSystem::WorldToHex(const fVec3& c, const fVec3& unitSize) {
	fVec2 halfSize = fVec2(unitSize.x, unitSize.z) * 0.5;
	float yCoord         = c.y / unitSize.y;
	//Center on 0,0
	fVec2 coord = fVec2(c.x + halfSize.x, c.z + halfSize.y);
	fVec2 absoluteSign  = fVec2(Maths::Sign(coord.x), Maths::Sign(coord.y));
	//Operations to get location given coord.x
	float fractPart = fmod(coord.x, 3.0 * halfSize.x);
	float intPart   = (float)((int)(coord.x / (3.0 * halfSize.x)));
	if (coord.x < 0.0)
		intPart = intPart - 1.0;
	//The smaller rectangle
	if (fractPart >= (2.0 * halfSize.x) || (fractPart <= 0.0 && fractPart > -halfSize.x)) {
		float  oddOffset = coord.y - halfSize.y;
		return fVec3( (2.0 * intPart + 1.0), yCoord, (int)(oddOffset * 0.5 / halfSize.y) - (  oddOffset < 0.0 ? 1.0f : 0.0f)); //Fuck this line
	}
	//The widder rectangle
	fVec3 ret = fVec3(2.0 * intPart + (absoluteSign.x < 0.0f ? 1.0f : 0.0f), yCoord, (int)(coord.y * 0.5 / halfSize.y));
	if (absoluteSign.y < 0.0)
		ret.z      = ret.z - 1.0;

	fVec2 rectPos  = fVec2(3.0   * intPart * halfSize.x +  (1.0 +  2.0 * (float)(absoluteSign.x == -1.0f) ) * halfSize.x, 
						   2.0   * ret.z   * halfSize.y +  halfSize.y); //DONT MULTIPLY SECOND PART BY absoluteSign.y
	fVec2 localPos = coord - rectPos;
	//Restriction to upper right quarter of the rectangle
	fVec2 localPosRest  = fVec2(abs(localPos.x), abs(localPos.y));
	fVec2 localSign     = fVec2(Maths::Sign(localPos.x), Maths::Sign(localPos.y));
	
	fVec3 rectSideVec    = fVec3(0.5 * halfSize.x - halfSize.x, halfSize.y, 0.0);
	fVec3 vec            = fVec3(localPosRest.x - halfSize.x, localPosRest.y, 0.0);

	fVec3 tempProduct    = vec.Cross(rectSideVec); // the Z component indicates 
	if (tempProduct.z <= 0.0)
		return ret;
	fVec2 temp = fVec2(ret.x, ret.z);
	temp = temp + fVec2(Maths::Sign(localPos.x), Maths::Min<float>(Maths::Sign(localPos.y), 0.0f));
	return fVec3(temp.x, ret.y, temp.y);
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