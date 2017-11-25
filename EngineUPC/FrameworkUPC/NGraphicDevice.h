#pragma once

#include <GL\glew.h>
#include "NColor.h"
#include "NDepthRenderTarget.h"

class GameFramework;

class NGraphicDevice
{
public:
	NGraphicDevice(GameFramework* framework) {
		mFramework = framework;
	}
	~NGraphicDevice() {
		mFramework = nullptr;
	}

	int GetScreenWidth() { return mScreenWidth; }
	int GetScreenHeight() { return mScreenHeight; }

	void Initialize(int screenWidth, int screenHeight);
	void SetClearColor(NColor clearColor);
	void ChangeTo2D();
	void ChangeTo3D();

	NDepthRenderTarget* CreateDepthRenderTarget(int width, int height);

	void Update(float dt);
	void Draw(float dt);

private:
	GameFramework* mFramework;

	int mScreenWidth;
	int mScreenHeight;
};

