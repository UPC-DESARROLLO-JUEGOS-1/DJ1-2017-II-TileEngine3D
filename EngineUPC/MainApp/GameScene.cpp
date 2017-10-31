#include "GameScene.h"
#include <FrameworkUPC\GameFramework.h>

#include <iostream>

void GameScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();

	// Creamos la camara
	Camera2D* camera = cManagement->CreateCamera2D(framework->GetScreenWidth(), 
		framework->GetScreenHeight());
	// Seteamos como la actual
	cManagement->SetCurrentCamera(camera);
}

void GameScene::OnKeyDown(SDL_Keycode key)
{

}

void GameScene::OnKeyUp(SDL_Keycode key)
{

}

void GameScene::Update(float dt)
{

}

void GameScene::Draw(float dt)
{

}
