#include "Noise.h"
#include <random>
#include <math.h>
#include "Log.h"

//Maybe won't use //static std::mt19937_64 rand64;

//LCG64 it hashes a seed to normalize it for srand()
uint32 lcg64(const uint64_t& seed) {
	uint32 x = (6364136223846793005ULL * seed + 1) >> 32;
	x ^= x >> 11;
	x ^= x << 7 & 0x9D2C5680;
	x ^= x << 15 & 0xEFC60000;
	x ^= x >> 18;
	return x;
}

float Noise::Random(fVec2 position) {
	std::srand( lcg64( ((uint64)(position.x) << 32) ^ (uint64)(position.y)) );
	return (double)std::rand() / (double)RAND_MAX;
}

void Noise::Init() {

}

float Noise::ValueNoise(fVec2 position) {
	fVec2 pos      = Maths::Floor(position);
	fVec2 localPos = Maths::Fract(position);
	float a        = Noise::Random(pos);
	float b        = Noise::Random(pos + fVec2(1.0, 0.0));
	float c        = Noise::Random(pos + fVec2(1.0, 1.0));
	float d        = Noise::Random(pos + fVec2(0.0, 1.0));

	fVec2 pp  = localPos * localPos;
	fVec2 ppp = pp * localPos;
	fVec2 xy  = pp * 3.0 -  ppp * 2.0;

	float interX  = Maths::lerp(a, b, xy.x);
	float interX2 = Maths::lerp(d, c, xy.x);
	return Maths::lerp(interX, interX2, xy.y);
}

float Noise::FBM(fVec2 position) {
	float ret = 0.0f;
	ret  += Noise::ValueNoise(position);
	ret  += (0.5     * Noise::ValueNoise(position  * 2.0f));
	ret  += (0.25    * Noise::ValueNoise(position  * 4.0f));
	ret  += (0.125   * Noise::ValueNoise(position  * 8.0f));
	ret  += (0.0625  * Noise::ValueNoise(position  * 16.0f));
	ret  += (0.03125 * Noise::ValueNoise(position  * 32.0f));
	ret  /= 1.5;
	return Maths::Min<float>(ret, 1.0f);
}

float Noise::FBMWrap(fVec2 position) {
	fVec2 a   = fVec2(Noise::FBM(position * 10.0), 
					  Noise::FBM(position * 10.0 + fVec2(1.6, 1.3)));

	fVec2 b   = fVec2(Noise::FBM(position * 5.0 + a * 2.0), 
					  Noise::FBM(position * 5.0 + a * 4.0));

	return Noise::FBM(b) * 0.5;
}