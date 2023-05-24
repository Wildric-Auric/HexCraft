#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Texture.h"
#include "stb/stb_image.h"
#include "Log.h"
#include "glew.h"
#include "glfw3.h"

Image::Image(std::string path) {
	stbi_set_flip_vertically_on_load(1);
	this->path  = path;
	this->data  = stbi_load(path.c_str(), &this->resolution.x, &this->resolution.y, &this->channels, 0);
}

void Image::Clear() {
	stbi_image_free(this->data);
	this->data = nullptr;
}



void Texture::SetUp() {
	glGenTextures(1, &this->id);
	this->Bind();
	
	bool   genMipMap   = (this->__prop.downScalingFiltering != GL_LINEAR) && (this->__prop.downScalingFiltering != GL_NEAREST);
	uint32 imageColorFormat = GL_RGBA;
	if (this->__imageInfo.channels == 1) 
		imageColorFormat = GL_RED;
	if (this->__imageInfo.channels == 3)
		imageColorFormat = GL_RGB;


	int texWrapping = this->__prop.repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->__prop.downScalingFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->__prop.upScalingFiltering);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texWrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texWrapping);

	//TODO::Custom internal format in properties? 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 
				 this->__imageInfo.resolution.x, this->__imageInfo.resolution.y, 0, 
				 imageColorFormat, GL_UNSIGNED_BYTE, this->__imageInfo.data);
	if (genMipMap)
		glGenerateMipmap(GL_TEXTURE_2D);
}


void Texture::Bind(uint8 samplerSlot) {
	glActiveTexture(GL_TEXTURE0 + samplerSlot);
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::Delete() {
	glDeleteTextures(1, &this->id);
	this->id = 0;
}

Texture::Texture(std::string path) {
	if (path == "")
		return;
	Image image =  Image(path);
	this->__imageInfo = image;
	this->SetUp();
	this->__imageInfo.Clear();
}

Texture::Texture(const FilteringProperties& prop, const Image& image) {
	if (image.path == "") {
		LOG_WARNING("Passed empty image to texture");
		return;
	}
	this->__imageInfo = image;
	this->__prop = prop;
	this->SetUp();
}

Texture::Texture(const Image& image) {
	if (image.path == "") {
		LOG_WARNING("Passed empty image to texture");
		return;
	}
	this->__imageInfo = image;
	this->SetUp();
}

