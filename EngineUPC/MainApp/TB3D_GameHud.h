#pragma once

#include <SDL\SDL.h>
#include <FrameworkUPC\Quad.h>
#include <FrameworkUPC\Sprite.h>
#include <FrameworkUPC\Button.h>

class BaseScene;

class TB3D_GameHud
{
public:
	TB3D_GameHud(BaseScene* scene);
	~TB3D_GameHud() {
		delete mScene;
	}

	void Initialize();
	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);
	void Update(float dt);
	void Draw(float dt);
	void UpdateLives(int lives);

private:
	BaseScene* mScene;
	std::vector<Sprite*> *heart;
	Button *btnNew;
	Quad* mQuad;
	int lives;

};

