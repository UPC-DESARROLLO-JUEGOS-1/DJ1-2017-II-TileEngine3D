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

	float size = mEngine->GetTileSize();

	this->CreateCollision(size);

	mDebugMode = false	;
	mOffsetX = -(mEngine->GetTileSize() / 2.0);
	mOffsetZ = -(mEngine->GetTileSize() / 2.0);

	mPlane = new NTexturePlane3D();
	mPlane->Initialize(0, 0, 0, size, size, file);
	mPlane->SetRenderCamera((BaseCamera*)mEngine->GetCamera()->GetRenderCamera());
}

void TB3D_Entity::Update(float dt) {
	TB3D_Actor::Update(dt);

	if (mPlane != nullptr) {
		mPlane->SetPosition(mX + mOffsetX, mY + mOffsetY, mZ + mOffsetZ);
		mPlane->SetRotationZ(3.1416);
		mPlane->SetRotationY(0.8);
		mPlane->Update(dt);
	}
}

void TB3D_Entity::Draw(float dt) {
	TB3D_Actor::Draw(dt);

	if (mPlane != nullptr) {
		mPlane->Draw(dt);
	}
}