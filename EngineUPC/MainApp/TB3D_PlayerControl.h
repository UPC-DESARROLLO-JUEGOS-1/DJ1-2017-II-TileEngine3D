#pragma once

#include <SDL\SDL_keycode.h>
#include "TB3D_Camera.h"

class TB3D_Player;

class TB3D_PlayerControl
{
public:
	TB3D_PlayerControl(TB3D_Player* player);
	~TB3D_PlayerControl();

	bool GetIsJumping() { return mIsJumping; }
	bool GetIsFalling() { return mIsFalling; }

	void DoJump();

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void Update(float dt);

private:
	TB3D_Player* mPlayer;

	bool mCanGoLeft;
	bool mCanGoRight;
	bool mCanGoForward;
	bool mCanGoBackward;
	bool mIsJumping;
	bool mIsFalling;

	float mPlayerSpeed;

	glm::vec3 mForces;

	int mDirectionX;
	int mDirectionY;

	Vector3 mDebugRotation;
};

