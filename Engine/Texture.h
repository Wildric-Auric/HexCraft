#pragma once

#include "Globals.h"
#include <string>


#define HEXC_DEFAULT_IMAGE ""


#define TEX_FILTER_NEAREST                     0x2600
#define TEX_FILTER_LINEAR					   0x2601
#define TEX_FILTER_NEAREST_FROM_NEAREST_MIPMAP 0x2700
#define TEX_FILTER_LINEAR_FROM_NEAREAST_MIPMAP 0x2701
#define TEX_FILTER_NEAREST_FROM_LINEAR_MIPMAP  0x2702
#define TEX_FILTER_LINEAR_FROM_LINEAR_MIPMAP   0x2703


typedef uint32 SampleMode;


class Image {
public:
	Image() {};
	Image(std::string path);
	void Clear();

	//data member contains pixels, should be cleared after being passed to Texture in general
	std::string path = "";
	uint8* data      = nullptr;
	iVec2  resolution;
	int    channels  = 0;
};




struct FilteringProperties {
	bool repeat				         = 0;
	SampleMode downScalingFiltering  = TEX_FILTER_NEAREST_FROM_LINEAR_MIPMAP;
	SampleMode upScalingFiltering    = TEX_FILTER_NEAREST;
};


class Texture {
private:
	uint32 id = 0;
	void SetUp();
public:
	FilteringProperties __prop;
	Image __imageInfo;

	Texture() {};
	Texture(const FilteringProperties& prop, const Image& image);
	Texture(const Image& image);
	//This constructor loads an image and clears its data automatically
	Texture(std::string path);

	void Bind(uint8 samplerSlot = 0);
	void Delete();
	
};