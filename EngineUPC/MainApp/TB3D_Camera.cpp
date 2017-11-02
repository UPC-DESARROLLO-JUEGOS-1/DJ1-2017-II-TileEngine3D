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
	mRenderCamera = cManagement->CreateCamera3D(cWidth, cHeight, PiOver4, 0.01f, 1000.0f);
	//mRenderCamera->SetPosition(0, 0, 0); // hard coded :)
	mRenderCamera->SetRotationX(-0.8f);
	//mRenderCamera->UpdownRot = 0.879999518f; // hard coded :)
	//mRenderCamera->LeftrightRot = 3.72529030e-08f; // hard coded :)
	
	cManagement->SetCurrentCamera(mRenderCamera);
}

void TB3D_Camera::Update(float dt) {
	if (mActor != nullptr) {
		mRenderCamera->SetPosition(
			-mActor->GetX(), 
			- 15,
			20 -mActor->GetZ()
			
		);
	}

	
	mRenderCamera->Update(dt);
}