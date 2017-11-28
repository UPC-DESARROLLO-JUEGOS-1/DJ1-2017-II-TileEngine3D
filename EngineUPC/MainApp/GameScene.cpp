#include "GameScene.h"
#include <FrameworkUPC\GameFramework.h>
#include "EnumAppScenes.h"

void GameScene::Initialize()
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	NCameraManagment* cManagement = framework->GetCameraManagement();
	framework->GetGraphicDevice()->ChangeTo2D();	

	bg = new Sprite();
	bg->Initialize(0, 0, "Sprites/bg.png");
	bg->SetRenderCamera(cManagement->GetCurrentCamera());

	btnNew = new Button();
	btnNew->Initialize(0, 0, "Sprites/btnNew.png");
	btnNew->SetX(framework->GetScreenWidth() / 2 - btnNew->GetWidth() / 2);
	btnNew->SetY(framework->GetScreenHeight() / 2 - btnNew->GetHeight() / 2 - 100);
	btnNew->SetRenderCamera(cManagement->GetCurrentCamera());

	btnExit = new Button();
	btnExit->Initialize(0, 0, "Sprites/btnExit.png");
	btnExit->SetX(framework->GetScreenWidth() / 2 - btnExit->GetWidth() / 2);
	btnExit->SetY(framework->GetScreenHeight() / 2 - btnExit->GetHeight() / 2 + 100);
	btnExit->SetRenderCamera(cManagement->GetCurrentCamera());
}

void GameScene::OnKeyDown(SDL_Keycode key)
{

}

void GameScene::OnKeyUp(SDL_Keycode key)
{

}

void GameScene::Update(float dt)
{
	bg->Update(dt);
	btnNew->Update(dt);
	btnExit->Update(dt);	
	
	if (btnNew->isClicked()) {
		GameFramework::GET_FRAMEWORK()->GetSceneGraph()->GoToScene(Juego);
	}else	
	if (btnExit->isClicked()) {
		GameFramework::GET_FRAMEWORK()->SetFrameworkState(FrameworkState::Exit);
	}	
}

void GameScene::Draw(float dt)
{
	bg->Draw(dt);
	btnNew->Draw(dt);
	btnExit->Draw(dt);
}
