#include "GameTile3DEngineScene.h"

void GameTile3DEngineScene::Initialize()
{
	mGame->Initialize();
}

void GameTile3DEngineScene::OnKeyDown(SDL_Keycode key)
{
	mGame->OnKeyDown(key);
}

void GameTile3DEngineScene::OnKeyUp(SDL_Keycode key)
{
	mGame->OnKeyUp(key);
}

void GameTile3DEngineScene::Update(float dt)
{
	mGame->Update(dt);
}

void GameTile3DEngineScene::Draw(float dt)
{
	mGame->Draw(dt);
}
