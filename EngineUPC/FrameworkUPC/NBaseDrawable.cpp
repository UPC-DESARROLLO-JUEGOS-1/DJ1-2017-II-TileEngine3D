#include "NBaseDrawable.h"

NBaseDrawable::NBaseDrawable() :
	mVBO_ID(0), mIBO_ID(0),
	needMatrixUpdate(true),
	worldMatrix(1.0f) { }

NBaseDrawable::~NBaseDrawable() {
	mCurrentShader = nullptr;
	mRenderCamera = nullptr;
}
