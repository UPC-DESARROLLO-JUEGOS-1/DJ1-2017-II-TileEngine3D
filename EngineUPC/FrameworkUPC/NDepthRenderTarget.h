#pragma once

#include "NBaseRenderTarget.h"

class NDepthRenderTarget : public NBaseRenderTarget
{
public:
	NDepthRenderTarget() {}
	~NDepthRenderTarget() {}

	void Initialize();
	void CreateTexture(int width, int height);
};

