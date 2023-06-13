#include "CoordinateSystem.h"
#include "UnitHex.h"
#include "Noise.h"
#include <iostream>

static UnitHex tt;

fVec3 CoordinateSystem::HexToWorld(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = coord.x * unitSize.x * 0.75; //0.75
	ret.y = coord.y * unitSize.y;
	ret.z = coord.z * unitSize.z + ( (int(coord.x) % 2 != 0) ? unitSize.z * 0.5: 0.0); //pas bon ! seulement good en y 
	return ret;
}

fVec3 CoordinateSystem::WorldToHex(const fVec3& coord, const fVec3& unitSize) {
	fVec3 ret;
	ret.x = (4.0f / 3.0f) * (1.0 / unitSize.x) * coord.x;
	ret.y = (1.0f / unitSize.y)				   * coord.y;
	ret.z = (1.0f / unitSize.z)				   * coord.z - (int(ret.x) % 2 != 0 ? 0.5 : 0.0);

	return Maths::Floor(ret); 
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
int CoordinateSystem::HeightInWorld(fVec3 position) {
	fVec3 posHex= CoordinateSystem::WorldToHex(position, tt.size);
	//std::cout << posHex.x << ", " << posHex.z <<" ...aled ";
	return tt.hauteur * Noise::FBMWrap(fVec2((posHex.x, posHex.z) * (1.0f / 1000.0f) * 1.0));
}

