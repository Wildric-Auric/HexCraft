#include "Framebuffer.h"
#include "Context.h"
#include "glew.h"

FrameBuffer::FrameBuffer(const iVec2& size) {
	glGenFramebuffers(1, &frameBufferId);
	glGenRenderbuffers(1, &renderBufferId);

	renderTex = Texture();

	renderTex.__imageInfo.channels   = 3;
	renderTex.__imageInfo.resolution = size;
	renderTex.__imageInfo.path       = std::to_string((word)this);
	renderTex.__imageInfo.data;

	renderTex.__prop.downScalingFiltering = TEX_FILTER_LINEAR_FROM_LINEAR_MIPMAP;
	renderTex.__prop.upScalingFiltering   = TEX_FILTER_LINEAR;

	this->renderTex.SetUp();
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->renderTex.id, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderBufferId);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderBufferId);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferId);
}

void FrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Delete() {
	glDeleteRenderbuffers(1, &this->renderBufferId);
	glDeleteFramebuffers(1,  &this->renderBufferId);
	this->renderTex.Delete();
}
