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

	btnContinue = new Button();
	btnContinue->Initialize(0, 0, "Sprites/btnContinue.png");
	btnContinue->SetX(framework->GetScreenWidth() / 2 - btnContinue->GetWidth() / 2);
	btnContinue->SetY(framework->GetScreenHeight() / 2 - btnContinue->GetHeight() / 2);
	btnContinue->SetRenderCamera(cManagement->GetCurrentCamera());

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
	btnContinue->Update(dt);
	btnExit->Update(dt);	
	
	if (btnNew->isClicked()) {
		GameFramework::GET_FRAMEWORK()->GetSceneGraph()->GoToScene(GameTile3DEngine);
	}else
	if (btnContinue->isClicked()) {
		GameFramework::GET_FRAMEWORK()->GetSceneGraph()->GoToScene(GameTile3DEngine);
	}else
	if (btnExit->isClicked()) {
		GameFramework::GET_FRAMEWORK()->SetFrameworkState(FrameworkState::Exit);
	}	
}

void GameScene::Draw(float dt)
{
	bg->Draw(dt);
	btnNew->Draw(dt);
	btnContinue->Draw(dt);
	btnExit->Draw(dt);
}
