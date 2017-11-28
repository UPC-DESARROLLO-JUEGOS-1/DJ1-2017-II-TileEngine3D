#pragma once

#include "TB3D_Entity.h"
#include "TB3D_PlayerControl.h"

#include <SDL\SDL_keycode.h>

class TB3D_Engine;

class TB3D_Player : public TB3D_Entity
{
public:
	TB3D_Player(TB3D_Engine* engine);
	~TB3D_Player();

	virtual void Initialize(std::string file);

	virtual void OnKeyDown(SDL_Keycode key) { mPlayerControl->OnKeyDown(key); }
	virtual void OnKeyUp(SDL_Keycode key) { mPlayerControl->OnKeyUp(key); }

	virtual void Update(float dt);
	virtual void Draw(float dt);
	TB3D_PlayerControl* GetPlayerControl();

private:
	TB3D_PlayerControl* mPlayerControl;

	NTexturePlane3D* mPlane;
};

