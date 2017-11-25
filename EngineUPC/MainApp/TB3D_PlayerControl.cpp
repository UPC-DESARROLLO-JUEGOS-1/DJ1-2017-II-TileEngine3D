#include "TB3D_PlayerControl.h"
#include "TB3D_Player.h"
#include <FrameworkUPC\GameFramework.h>

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
	mIsJumping = false;
	mIsFalling = false;

	mDirectionX = 0;
	mDirectionY = 0;
	mForces = glm::vec3(0, 0, 0);

	mPlayerSpeed = 10;
	mDebugRotation = Vector3::Zero;
}

void TB3D_PlayerControl::DoJump() {
	if (!mIsFalling && !mIsJumping) {
		mIsJumping = true;
		mForces.y = 1.3f;
	}
}

void TB3D_PlayerControl::OnKeyDown(SDL_Keycode key) {
	NLightManager* lightManager = GameFramework::GET_FRAMEWORK()->GetLightManager();
	NBasicLight* light0 = lightManager->GetLigth("light0");

	glm::vec4 lightDir = light0->GetPosition();

	switch (key) {
	case SDLK_LEFT:
		mCanGoBackward = true;
		mDirectionX = 1;
		break;
	case SDLK_RIGHT:
		mCanGoForward = true;
		mDirectionX = -1;
		break;
	case SDLK_UP:
		mCanGoLeft = true;
		mDirectionY = 1;
		break;
	case SDLK_DOWN:
		mCanGoRight = true;
		mDirectionY = -1;
		break;
	case SDLK_a:
		mDebugRotation.z += 0.01f;
		mPlayer->GetCollisionCube()->SetRotationZ(mDebugRotation.z);
		break;
	case SDLK_w:
		mDebugRotation.y += 0.01f;
		mPlayer->GetCollisionCube()->SetRotationY(mDebugRotation.y);
		break;
	case SDLK_f:
		lightDir.x += 1;
		break;
	case SDLK_g:
		lightDir.y += 1;
		break;
	case SDLK_h:
		lightDir.z += 1;
		break;
	case SDLK_v:
		lightDir.x -= 1;
		break;
	case SDLK_b:
		lightDir.y -= 1;
		break;
	case SDLK_n:
		lightDir.z -= 1;
		break;
	case SDLK_SPACE:
		DoJump();
		break;
	}

	light0->SetPosition(lightDir.x, lightDir.y , lightDir.z);
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

	float positionY = mPlayer->GetY();
	Vector2 position = Vector2::Zero;
	
	if (mIsFalling || mIsJumping) {
		positionY += mForces.y;
		mForces.y -= 0.1f;

		if (mIsJumping) {
			if (mForces.y > 0) {
				mIsJumping = false;
				mIsFalling = true;
			}
		}
		else if (mIsFalling) {
			if (positionY < 0) {
				positionY = 0;
				mForces.y = 0;
				mIsFalling = false;
			}
		}

		float speed = mPlayerSpeed * dt;
		position.x = mPlayer->GetX() + (speed * mDirectionX);
		position.y = mPlayer->GetZ() + (speed * mDirectionY);
	}
	else {
		position = mPlayer->ComputeNewPosition(
			mPlayerSpeed * dt, 
			mDirectionX, 
			mDirectionY);
	}

	
	mPlayer->SetX(position.x);
	mPlayer->SetY(positionY);
	mPlayer->SetZ(position.y);

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NBasicLight* light = framework->GetLightManager()->GetLigth("light1");

	if (light != nullptr) {
		light->SetPosition(position.x, positionY + 2, position.y);
	}

	if (!mCanGoForward && !mCanGoBackward) { mDirectionX = 0; }
	if (!mCanGoLeft && !mCanGoRight) { mDirectionY = 0; }
}