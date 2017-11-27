#include "TB3D_EnemyControl.h"
#include "TB3D_Enemy.h"
#include <FrameworkUPC\GameFramework.h>
#include <iostream>

TB3D_EnemyControl::TB3D_EnemyControl(TB3D_Enemy* Enemy):
	min(1),
	max(4)
{
	begin = clock(); 
	mEnemy = Enemy;
	randomizer = Randomizer();
	r = (randomizer.GenerateRandom(min, max)) * CLOCKS_PER_SEC;
}

TB3D_EnemyControl::~TB3D_EnemyControl()
{
}

void TB3D_EnemyControl::Initialize() {
	mCanGoLeft = false;
	mCanGoRight = false;
	mCanGoForward = false;
	mCanGoBackward = false;

	mDirectionX = 0;
	mDirectionY = 0;

	mEnemySpeed = 3;
	mDebugRotation = Vector3::Zero;
	
}

void TB3D_EnemyControl::OnKeyDown(int option) {
	if (justMoved)
		return;

	NLightManager* lightManager = GameFramework::GET_FRAMEWORK()->GetLightManager();
	NBasicLight* light0 = lightManager->GetLigth("light0");

	glm::vec4 lightDir = light0->GetPosition();

	switch (option) {
	case 1:
		mCanGoBackward = true;
		mDirectionX = 1;
		break;
	case 2:
		mCanGoForward = true;
		mDirectionX = -1;
		break;
	case 3:
		mCanGoLeft = true;
		mDirectionY = 1;
		break;
	case 0:
		mCanGoRight = true;
		mDirectionY = -1;
		break;

		light0->SetPosition(lightDir.x, lightDir.y, lightDir.z);
		justMoved = true;
	}
}

void TB3D_EnemyControl::OnKeyUp(int option) {
	switch (option) {
	case 1:
		mCanGoBackward = false;
		break;
	case 2:
		mCanGoForward = false;
		break;
	case 3:
		mCanGoLeft = false;
		break;
	case 0:
		mCanGoRight = false;
		break;
	}
	justMoved = false;
}


void TB3D_EnemyControl::Update(float dt) {
	float newX = 0;
	float newY = 0;

	Vector2 position = mEnemy->ComputeNewPosition(mEnemySpeed * dt, mDirectionX, mDirectionY);

	mEnemy->SetX(position.x);
	mEnemy->SetZ(position.y);

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NBasicLight* light = framework->GetLightManager()->GetLigth("light1");

	if (light != nullptr) {
		light->SetPosition(position.x, light->GetPosition().y, position.y);
	}

	if (!mCanGoForward && !mCanGoBackward) { mDirectionX = 0; }
	if (!mCanGoLeft && !mCanGoRight) { mDirectionY = 0; }

	end = clock();

	
	if (long(end - begin) > r) {
		std::cout << r << " ";
		begin = clock();
		mEnemySpeed = randomizer.GenerateRandom(1, 10);
		r = (randomizer.GenerateRandom(min, max)) * CLOCKS_PER_SEC;
		for (int i = 0;i < 4; i++)
		{
			OnKeyUp(i);
		}
		RandomMovement();
	}
	
}

void TB3D_EnemyControl::RandomMovement() {
	OnKeyDown(randomizer.GenerateRandom(0, 3));
	OnKeyDown(randomizer.GenerateRandom(0, 3));
}