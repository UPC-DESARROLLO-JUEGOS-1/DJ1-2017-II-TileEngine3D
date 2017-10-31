#include "NCameraManagment.h"

NCameraManagment::~NCameraManagment()
{
}

Camera2D * NCameraManagment::CreateCamera2D(int screenWidth, int screenHeight)
{
	Camera2D* camera = new Camera2D();
	camera->Initialize(screenWidth, screenHeight);
	return camera;
}

Camera3D * NCameraManagment::CreateCamera3D(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
{
	Camera3D* camera = new Camera3D();
	camera->Initialize(screenWidth, screenHeight, fov, zNear, zFar);
	return camera;
}

FPSCamera * NCameraManagment::CreateFPSCamera(int screenWidth, int screenHeight, float fov, float zNear, float zFar)
{
	FPSCamera* camera = new FPSCamera();
	camera->Initialize(screenWidth, screenHeight, fov, zNear, zFar);
	return camera;
}

void NCameraManagment::Initialize()
{
}

void NCameraManagment::Update(float dt)
{
	if (mCurrentCamera != nullptr) {
		mCurrentCamera->Update(dt);
	}
}
