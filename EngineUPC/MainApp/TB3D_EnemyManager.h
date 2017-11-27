#pragma once
#include "TB3D_Enemy.h"
#include <vector>



class TB3D_EnemyManager
{
public:
	TB3D_EnemyManager(TB3D_Engine* engine);
	~TB3D_EnemyManager();

	void Initialize();

	void Update(float dt);
	void Draw(float dt);
	void AddAtPosition(float x, float y, float z);

	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

private:
	std::vector<TB3D_Enemy*> *enemies;
	TB3D_Engine *mEngine;
	int index;
};

