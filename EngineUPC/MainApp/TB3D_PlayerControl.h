#pragma once

#include <SDL\SDL_keycode.h>
#include "TB3D_Camera.h"

class TB3D_Player;

class TB3D_PlayerControl
{
public:
	TB3D_PlayerControl(TB3D_Player* player);
	~TB3D_PlayerControl();

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void Update(float dt);
	int GetLives();
	void SetLives(int lives);
private:
	TB3D_Player* mPlayer;

	bool mCanGoLeft;
	bool mCanGoRight;
	bool mCanGoForward;
	bool mCanGoBackward;

	bool justMoved;

	float mPlayerSpeed;

	int mDirectionX;
	int mDirectionY;

	Vector3 mDebugRotation;
	int lives;
	NBasicLight* light;
};

