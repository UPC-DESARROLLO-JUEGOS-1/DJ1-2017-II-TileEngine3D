#include "TB3D_Entity.h"

#include "TB3D_Engine.h"

TB3D_Entity::TB3D_Entity(TB3D_Engine* engine) : TB3D_Actor(engine)
{
}

TB3D_Entity::~TB3D_Entity()
{
	TB3D_Actor::~TB3D_Actor();
}

void TB3D_Entity::CreateCollision(float size) {
	mCollisionCube = new NPrimitiveCube3D();
	mCollisionCube->Initialize(0, 0, 0, size, size, 1);
	mCollisionCube->SetColor(NColor::Blue);
	mCollisionCube->SetRenderCamera((BaseCamera*)mEngine->GetCamera()->GetRenderCamera());
}

void TB3D_Entity::Initialize(std::string file) {
	TB3D_Actor::Initialize();

	this->CreateCollision(4.0);

	mDebugMode = false	;
	mOffsetX = -(mEngine->GetTileSize() / 2.0);
	mOffsetZ = -(mEngine->GetTileSize() / 2.0);

	mPlane = new NTexturePlane3D();
	mPlane->Initialize(0, 0, 0, 4.0f, 4.0f, file);
	mPlane->SetRenderCamera((BaseCamera*)mEngine->GetCamera()->GetRenderCamera());
}

void TB3D_Entity::Update(float dt) {
	TB3D_Actor::Update(dt);

	if (mPlane != nullptr) {
		mPlane->SetPosition(mX + mOffsetX, mY + mOffsetY, mZ + mOffsetZ);
		mPlane->Update(dt);
	}
}

void TB3D_Entity::Draw(float dt) {
	TB3D_Actor::Draw(dt);

	if (mPlane != nullptr) {
		mPlane->Draw(dt);
	}
}