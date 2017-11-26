#pragma once

#include <FrameworkUPC\BaseScene.h>
#include <FrameworkUPC\Button.h>
#include <FrameworkUPC\Sprite.h>

class GameScene : public BaseScene
{
public:
	GameScene(SceneGraph* sceneGraph) :
		BaseScene::BaseScene(sceneGraph)
	{}
	~GameScene()
	{
		
	}

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

	void OnKeyDown(SDL_Keycode key);
	void OnKeyUp(SDL_Keycode key);

private:
	Button *btnNew, *btnExit, *btnContinue;
	Sprite* bg;	
};