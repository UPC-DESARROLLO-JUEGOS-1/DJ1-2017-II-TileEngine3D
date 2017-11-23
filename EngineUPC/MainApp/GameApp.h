#pragma once

#include <FrameworkUPC\GameFramework.h>
#include "TB3D_TurnManager.h"

#include <functional>

class GameApp
{
public:
	GameApp();
	~GameApp();

	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	void Start();
	TB3D_TurnManager turnManager;

private:
	GameFramework frameWork;
	
	void InitializeApp();
	void OnInput(SDL_Event evnt);
	void Update(float dt);
	void Draw(float dt);

};