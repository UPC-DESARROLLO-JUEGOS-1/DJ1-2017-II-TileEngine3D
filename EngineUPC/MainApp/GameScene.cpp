#include "GameScene.h"
#include <FrameworkUPC\GameFramework.h>

#include <iostream>

void GameScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();
	framework->GetGraphicDevice()->ChangeTo2D();
	
	mButton = new Button();
	mButton->Initialize(10, 10, "Sprites/btnstart.png");
	mButton->SetRenderCamera(cManagement->GetCurrentCamera());
}





void GameScene::OnKeyDown(SDL_Keycode key)
{

}

void GameScene::OnKeyUp(SDL_Keycode key)
{

}

void GameScene::Update(float dt)
{
	mButton->Update(dt);
}

void GameScene::Draw(float dt)
{
	mButton->Draw(dt);
}
