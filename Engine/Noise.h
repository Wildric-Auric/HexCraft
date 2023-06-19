#pragma once
#include "Globals.h"
#include <random>

class Noise {
public:
	//Return a random number between 0 and 1 given a position
	static void  Init();
	static float Random(fVec2 position);	
	static float ValueNoise(fVec2 position);
	static float FBM(fVec2 postion);
	static float FBMWrap(fVec2 position);
};