#include "GameMainMenu.h"

void GameMainMenu::Initialize()
{
	mGame->Initialize();
}

void GameMainMenu::OnKeyDown(SDL_Keycode key)
{
	mGame->OnKeyDown(key);
}

void GameMainMenu::OnKeyUp(SDL_Keycode key)
{
	mGame->OnKeyUp(key);
}

void GameMainMenu::Update(float dt)
{
	mGame->Update(dt);
}

void GameMainMenu::Draw(float dt)
{
	mGame->Draw(dt);
}
