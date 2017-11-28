#include "TB3D_Enemy.h"

#include "TB3D_Engine.h"

TB3D_Enemy::TB3D_Enemy(TB3D_Engine* engine) : TB3D_Entity(engine)
{
	mEnemyControl = new TB3D_EnemyControl(this);
}

TB3D_Enemy::~TB3D_Enemy()
{
	delete mEnemyControl;

	TB3D_Entity::~TB3D_Entity();
}

void TB3D_Enemy::Initialize(std::string file) {
	TB3D_Entity::Initialize(file);

	mEnemyControl->Initialize();
}

void TB3D_Enemy::Update(float dt) {
	TB3D_Entity::Update(dt);

	mEnemyControl->Update(dt);
}

void TB3D_Enemy::Draw(float dt) {
	TB3D_Entity::Draw(dt);
}

