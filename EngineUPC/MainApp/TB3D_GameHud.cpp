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
	else if (heart->size() < lives){
		//heart->push_back(new Sprite(90 * (lives - 1) + 20, 20, "Sprites/life.png"));
		//heart->at(heart->size()-1)->SetRenderCamera(GameFramework::GET_FRAMEWORK()->GetCameraManagement()->GetCurrentCamera());
	}
}

void TB3D_GameHud::Draw(float dt) {
	mQuad->Draw(dt);
	for (int i = 0; i < heart->size(); i++) {
		heart->at(i)->Draw(dt);
	}
}
