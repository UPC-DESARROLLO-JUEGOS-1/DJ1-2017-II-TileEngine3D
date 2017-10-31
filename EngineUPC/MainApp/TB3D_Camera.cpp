#include "TB3D_Camera.h"
#include "TB3D_Engine.h"

#include <FrameworkUPC\GameFramework.h>
#include <FrameworkUPC\NCameraManagment.h>

#define PiOver4 3.14159265 / 4.0f

TB3D_Camera::TB3D_Camera(TB3D_Engine* engine)
{
	mEngine = engine;
}


TB3D_Camera::~TB3D_Camera()
{
}

void TB3D_Camera::Initialize() {
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();

	int cWidth = framework->GetScreenWidth();
	int cHeight = framework->GetScreenHeight();

	// Creamos la camara
	mRenderCamera = cManagement->CreateFPSCamera(cWidth, cHeight, PiOver4, 0.01f, 1000.0f);
	
	cManagement->SetCurrentCamera(mRenderCamera);
}

void TB3D_Camera::Update(float dt) {
	mRenderCamera->Update(dt);
}