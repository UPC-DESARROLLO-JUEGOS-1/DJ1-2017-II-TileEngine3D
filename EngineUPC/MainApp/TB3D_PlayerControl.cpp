#include "TB3D_PlayerControl.h"
#include "TB3D_Player.h"

TB3D_PlayerControl::TB3D_PlayerControl(TB3D_Player* player)
{
	mPlayer = player;
}

TB3D_PlayerControl::~TB3D_PlayerControl()
{
}

void TB3D_PlayerControl::Initialize() {
	mCanGoLeft = false;
	mCanGoRight = false;
	mCanGoForward = false;
	mCanGoBackward = false;

	mDirectionX = 0;
	mDirectionY = 0;

	mPlayerSpeed = 10;
}

void TB3D_PlayerControl::OnKeyDown(SDL_Keycode key) {
	switch (key) {
	case SDLK_LEFT:
		mCanGoBackward = true;
		mDirectionX = -1;
		break;
	case SDLK_RIGHT:
		mCanGoForward = true;
		mDirectionX = 1;
		break;
	case SDLK_UP:
		mCanGoLeft = true;
		mDirectionY = -1;
		break;
	case SDLK_DOWN:
		mCanGoRight = true;
		mDirectionY = 1;
		break;
	}
}

void TB3D_PlayerControl::OnKeyUp(SDL_Keycode key) {
	switch (key) {
	case SDLK_LEFT:
		mCanGoBackward = false;
		break;
	case SDLK_RIGHT:
		mCanGoForward = false;
		break;
	case SDLK_UP:
		mCanGoLeft = false;
		break;
	case SDLK_DOWN:
		mCanGoRight = false;
		break;
	}
}


void TB3D_PlayerControl::Update(float dt) {
	float newX = 0;
	float newY = 0;

	Vector2 position = mPlayer->ComputeNewPosition(mPlayerSpeed * dt, mDirectionX, mDirectionY);
	
	mPlayer->SetX(position.x);
	mPlayer->SetZ(position.y);

	
	
	if (!mCanGoForward && !mCanGoBackward) { mDirectionX = 0; }
	if (!mCanGoLeft && !mCanGoRight) { mDirectionY = 0; }
}