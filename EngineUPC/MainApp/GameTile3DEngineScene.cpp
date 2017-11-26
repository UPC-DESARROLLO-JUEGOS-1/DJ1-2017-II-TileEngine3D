#include "GameTile3DEngineScene.h"
#include <FrameworkUPC\GameFramework.h>

void GameTile3DEngineScene::Initialize()
{
	profileManager = TB3D_ProfileManger();

	//1. Parse json DOM "d" from loaded file named "profile".json
	json = profileManager.load("Saves/profile");
	d.Parse(json);
	//cout << "Current HP: " << to_string(((Value&)d["currentHp"]).GetInt()) << endl;
	//cout << "Current i Location: " << to_string(((Value&)d["location"]["i"]).GetInt()) << endl;
	
	//SetProfile(1); // ¿Como pasar parametro desde escena previa?
	//UpdateProfile();
	//SaveProfile();
	
	GameFramework* framework = GameFramework::GET_FRAMEWORK();

	// inicializamos en 3D
	framework->GetGraphicDevice()->ChangeTo3D();
	mGame->Initialize();

	// inicializamos 2D
	framework->GetGraphicDevice()->ChangeTo2D();
	mGameHud->Initialize();

	// Turn Manager
	std::queue<int> entitiesTypes = std::queue<int>();
	for (int i = 0; i < 10; i++) {
		entitiesTypes.push(rand() % 7);
	}

	turnManager.Initialize(entitiesTypes.size(), entitiesTypes);
	turnManager.GenerateTurns();

	int type = -1;
	do {
		type = turnManager.GetNextTurn();
	} while (type >= 0);

	
}
void GameTile3DEngineScene::SetProfile(int option) {
	//2. Setup profile from (previously loaded) DOM.	
	switch (option)
	{
	case 1:
		profile = profileManager.SetupProfile(&d); 
		break;
	default:
		profile = Profile();
		break;
	}
}
void GameTile3DEngineScene::UpdateProfile() {
	//3. Update profile values at will
	profile.SetCurrenHp(profile.GetCurrenHp() + 1);
}
void GameTile3DEngineScene::SaveProfile() {
	//4. Update DOM from profile info.
	profileManager.SaveProfileToDOM(profile, &d);

	//5. Stringify the DOM.
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);

	//6. Save buffered DOM string to file "profile" 
	profileManager.save("Saves/profile", buffer.GetString());
}

void GameTile3DEngineScene::OnKeyDown(SDL_Keycode key)
{
	mGame->OnKeyDown(key);
	mGameHud->OnKeyDown(key);
}

void GameTile3DEngineScene::OnKeyUp(SDL_Keycode key)
{
	mGame->OnKeyUp(key);
	mGameHud->OnKeyUp(key);
}

void GameTile3DEngineScene::Update(float dt)
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	
	// actualizamos 3D
	framework->GetGraphicDevice()->ChangeTo3D();
	mGame->Update(dt);

	// actualizamos 2D
	framework->GetGraphicDevice()->ChangeTo2D();
	mGameHud->Update(dt);
}

void GameTile3DEngineScene::Draw(float dt)
{
	GameFramework* framework = GameFramework::GET_FRAMEWORK();

	// dibujamos 3D
	framework->GetGraphicDevice()->ChangeTo3D();
	mGame->Draw(dt);

	// dibujamos 2D
	framework->GetGraphicDevice()->ChangeTo2D();
	mGameHud->Draw(dt);
}
