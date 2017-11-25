#pragma once

#include <GL\glew.h>

class NBaseRenderTarget
{
public:
	NBaseRenderTarget() :
		mSuccesfulCreation(false) {}
	~NBaseRenderTarget() {}

	bool GetSuccesfulCreation() { return mSuccesfulCreation; }
	GLuint GetTextureId() { return mTextureId; }
	GLuint GetFBOId() { return mFBOId; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

	virtual void Initialize();
	virtual void CreateTexture(int width, int height) {
		mWidth = width;
		mHeight = height;
	}
	virtual void Set() {
		// attach the texture to FBO depth attachment point
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mTextureId, 0);
	}
	virtual void Unset() {
		// switch back to window-system-provided framebuffer
		glBindFramebufferEXT(GL_FRAMEBUFFER, 0);
	}

protected:
	int mWidth, mHeight;

	GLuint mTextureId;
	GLuint mFBOId;

	bool mSuccesfulCreation;
};

