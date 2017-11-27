#pragma once

#include "TB3D_Entity.h"
#include "TB3D_EnemyControl.h"

#include <SDL\SDL_keycode.h>

class TB3D_Engine;

class TB3D_Enemy : public TB3D_Entity
{
public:
	TB3D_Enemy(TB3D_Engine* engine);
	~TB3D_Enemy();

	virtual void Initialize(std::string file);

	virtual void OnKeyDown(SDL_Keycode key) { mEnemyControl->OnKeyDown(key); }
	virtual void OnKeyUp(SDL_Keycode key) { mEnemyControl->OnKeyUp(key); }

	virtual void Update(float dt);
	virtual void Draw(float dt);

private:
	TB3D_EnemyControl* mEnemyControl;

	NTexturePlane3D* mPlane;
};

