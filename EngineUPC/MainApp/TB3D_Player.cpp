#include "TB3D_Player.h"

#include "TB3D_Engine.h"

TB3D_Player::TB3D_Player(TB3D_Engine* engine) : TB3D_Entity(engine)
{
	mPlayerControl = new TB3D_PlayerControl(this);
}

TB3D_Player::~TB3D_Player()
{
	delete mPlayerControl;

	TB3D_Entity::~TB3D_Entity();
}

void TB3D_Player::Initialize(std::string file) {
	TB3D_Entity::Initialize(file);

	mPlayerControl->Initialize();
}

void TB3D_Player::Update(float dt) {
	TB3D_Entity::Update(dt);

	mPlayerControl->Update(dt);	
}

void TB3D_Player::Draw(float dt) {
	TB3D_Entity::Draw(dt);
}

TB3D_PlayerControl* TB3D_Player::GetPlayerControl() {
	return mPlayerControl;
}