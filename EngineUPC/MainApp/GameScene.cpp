#include "GameScene.h"
#include <FrameworkUPC\GameFramework.h>

#include <iostream>

void GameScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();
	framework->GetGraphicDevice()->ChangeTo2D();
	
	mQuad = new Quad();
	mQuad->Initialize(10, 10, 80, 80);
	mQuad->SetRenderCamera(cManagement->GetCurrentCamera());
}

void GameScene::OnKeyDown(SDL_Keycode key)
{

}

void GameScene::OnKeyUp(SDL_Keycode key)
{

}

void GameScene::Update(float dt)
{
	mQuad->Update(dt);
}

void GameScene::Draw(float dt)
{
	mQuad->Draw(dt);
}
