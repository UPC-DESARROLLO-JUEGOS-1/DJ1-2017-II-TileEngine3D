#pragma once

#include <SDL\SDL_keycode.h>
#include "TB3D_Camera.h"
#include <random>
#include <ctime>
#include "Randomizer.h"

class TB3D_Enemy;

class TB3D_EnemyControl
{
public:
	TB3D_EnemyControl(TB3D_Enemy* Enemy);
	~TB3D_EnemyControl();

	void Initialize();

	void OnKeyDown(int option);
	void OnKeyUp(int option);
	void Update(float dt);

	void FollowPlayer(bool follow);
	void SetChaseDir(float xDir, float yDir);
	void RandomMovement();
	Randomizer randomizer;
private:
	TB3D_Enemy* mEnemy;

	bool mCanGoLeft;
	bool mCanGoRight;
	bool mCanGoForward;
	bool mCanGoBackward;

	bool justMoved;

	float mEnemySpeed;

	int mDirectionX;
	int mDirectionY;

	Vector3 mDebugRotation;

	clock_t begin;
	clock_t end;
	long r;
	unsigned int min, max;	
	bool followsPlayer;
};
