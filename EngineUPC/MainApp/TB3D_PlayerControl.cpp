#include "TB3D_PlayerControl.h"
#include "TB3D_Player.h"
#include <FrameworkUPC\NColor.h>
#include <FrameworkUPC\GameFramework.h>

TB3D_PlayerControl::TB3D_PlayerControl(TB3D_Player* player):
	lives(3)
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
	mDebugRotation = Vector3::Zero;

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	light = framework->GetLightManager()->GetLigth("light1");
}

void TB3D_PlayerControl::OnKeyDown(SDL_Keycode key) {
	if (justMoved)
		return;

	NLightManager* lightManager = GameFramework::GET_FRAMEWORK()->GetLightManager();
	NBasicLight* light0 = lightManager->GetLigth("light0");

	glm::vec4 lightDir = light0->GetPosition();
	int offset = 5;
	switch (key) {
	case SDLK_LEFT:
		mCanGoBackward = true;
		mDirectionX = 1;
		if (light != nullptr) {
			light->SetPosition(mPlayer->GetX() - offset, light->GetPosition().y, mPlayer->GetZ());
		}
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
	}
	light->SetPosition(lightDir.x, lightDir.y , lightDir.z);
	//justMoved = true;
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
	//justMoved = false;
}


void TB3D_PlayerControl::Update(float dt) {
	float newX = 0;
	float newY = 0;
	Vector2 position = mPlayer->ComputeNewPosition(mPlayerSpeed * dt, mDirectionX, mDirectionY);
	
	mPlayer->SetX(position.x);
	mPlayer->SetZ(position.y);
	
	if (lives == 1)
		light->SetLightColor(NColor::Red);
	else
		light->SetLightColor(NColor::White);
	

	if (light != nullptr) {
		light->SetPosition(position.x + mPlayer->mOffsetX, light->GetPosition().y, position.y + mPlayer->mOffsetZ);
		light->SetConeDirection(mDirectionX, -.8f, mDirectionY);
	}

	if (!mCanGoForward && !mCanGoBackward) { mDirectionX = 0; }
	if (!mCanGoLeft && !mCanGoRight) { mDirectionY = 0; }
}

int TB3D_PlayerControl::GetLives() {
	return lives;
}
void TB3D_PlayerControl::SetLives(int lives) {
	if(lives >= 0)
		this->lives = lives;
}