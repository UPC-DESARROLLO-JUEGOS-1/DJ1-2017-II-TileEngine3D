#include "TB3D_GameHud.h"
#include <FrameworkUPC\BaseScene.h>
#include <FrameworkUPC\GameFramework.h>

TB3D_GameHud::TB3D_GameHud(BaseScene* scene) :
	heart(new std::vector<Sprite*>())
{
	mScene = scene;
}

void TB3D_GameHud::Initialize() {


	
	mQuad = new Quad();
	mQuad->Initialize(10, 10, 80, 20);
	mQuad->SetRenderCamera(GameFramework::GET_FRAMEWORK()->GetCameraManagement()->GetCurrentCamera());
	for (int i = 0; i < lives; i++) {
		heart->push_back(new Sprite(90 * i + 20, 20, "Sprites/life.png"));
		heart->at(i)->SetRenderCamera(GameFramework::GET_FRAMEWORK()->GetCameraManagement()->GetCurrentCamera());
	}

	btnNew = new Button();
	//btnNew->Initialize(0, 0, "Sprites/btnNew.png");
	//btnNew->SetX(GameFramework::GET_FRAMEWORK()->GetScreenWidth() / 2 - btnNew->GetWidth() / 2);
	//btnNew->SetY(GameFramework::GET_FRAMEWORK()->GetScreenHeight() / 2 - btnNew->GetHeight() / 2 - 100);
	//btnNew->SetRenderCamera(GameFramework::GET_FRAMEWORK()->GetCameraManagement()->GetCurrentCamera());
}

void TB3D_GameHud::OnKeyDown(SDL_Keycode key) {

}

void TB3D_GameHud::OnKeyUp(SDL_Keycode key) {

}

void TB3D_GameHud::Update(float dt) {
	mQuad->Update(dt);
	for (int i = 0; i < heart->size(); i++) {
		heart->at(i)->Update(dt);
	}
}

void TB3D_GameHud::UpdateLives(int lives) {
	this->lives = lives;
	if (heart->size() > lives) {
		heart->pop_back();
	}
	else if (heart->size() > 0){
		for (int i = heart->size(); i < lives; i++) {
			heart->push_back(new Sprite(90 * i + 20, 20, "Sprites/life.png"));
			heart->at(heart->size() - 1)->SetRenderCamera(GameFramework::GET_FRAMEWORK()->GetCameraManagement()->GetCurrentCamera());
		}
		
	}
}

void TB3D_GameHud::Draw(float dt) {
	mQuad->Draw(dt);
	for (int i = 0; i < heart->size(); i++) {
		heart->at(i)->Draw(dt);
	}
}
