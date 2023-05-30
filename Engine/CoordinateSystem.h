#pragma once
#include "Globals.h"


class CoordinateSystem {
public:
	static fVec3 WorldToHex(const fVec3& coord, const fVec3& unitSize);
	static fVec3 HexToWorld(const fVec3& coord, const fVec3& unitSize);

	static fVec3 WorldToRect(const fVec3& coord, const fVec3& unitSize);
	static fVec3 RectToWorld(const fVec3& coord, const fVec3& unitSize);
};