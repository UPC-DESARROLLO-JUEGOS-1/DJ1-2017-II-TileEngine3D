#include "NBaseRenderTarget.h"

void NBaseRenderTarget::Initialize() {
	glGenFramebuffers(1, &mFBOId);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBOId);
}
