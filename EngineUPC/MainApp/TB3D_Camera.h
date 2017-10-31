#pragma once

#include <FrameworkUPC\FPSCamera.h>;

class TB3D_Engine;

class TB3D_Camera
{
public:
	TB3D_Camera(TB3D_Engine* engine);
	~TB3D_Camera();

	FPSCamera* GetRenderCamera() { return mRenderCamera; }

	void Initialize();
	void Update(float dt);

private:
	TB3D_Engine* mEngine;
	FPSCamera* mRenderCamera;
};

