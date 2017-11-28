#include "TB3D_EnemyManager.h"



TB3D_EnemyManager::TB3D_EnemyManager(TB3D_Engine* engine) :
	enemies(new std::vector<TB3D_Enemy*>()),
	index(0)
{
	mEngine = engine;
	beginDelay = clock();
	endDelay = clock();
}


TB3D_EnemyManager::~TB3D_EnemyManager()
{
}

void TB3D_EnemyManager::Initialize() {
	
}

void TB3D_EnemyManager::Update(float dt)
{
	endDelay = clock();
	for (int i = 0; i < enemies->size(); i++)
	{
		enemies->at(i)->Update(dt);
	}
}

void TB3D_EnemyManager::Draw(float dt)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		enemies->at(i)->Draw(dt);
	}
}

void TB3D_EnemyManager::AddAtPosition(float x, float y, float z)
{
	enemies->push_back( new TB3D_Enemy(mEngine));
	enemies->at(index)->Initialize("Sprites/enemy.png");
	enemies->at(index)->SetPosition(x, y, z);
	index++;
}

void TB3D_EnemyManager::OnKeyDown(SDL_Keycode key)
{
	
	enemies->at(index)->OnKeyDown(key);
	
}

void TB3D_EnemyManager::OnKeyUp(SDL_Keycode key)
{
	for (int i = 0; i < enemies->size(); i++)
	{
		//enemies->at(index)->OnKeyUp(key);
	}
}

bool TB3D_EnemyManager::DamagePlayer(double px, double py) {
	double x, y;
	bool damaged = false;
	for (int i = 0; i < enemies->size(); i++)
	{

		x = enemies->at(i)->GetX();
		y = enemies->at(i)->GetZ();
		double dist = sqrt((x - px)*(x - px) + (y - py)*(y - py));
		
		
		float delay = ((endDelay - beginDelay) / CLOCKS_PER_SEC);
		if (dist < 2.0f && delay > 0.25f) {
			beginDelay = clock();
			enemies->at(i)->GetEnemyControl()->DisableMovementFor(0.25f);
			//enemies->erase(enemies->begin()+i);
			damaged = true;
		}else if (dist < 10.0f) {
			enemies->at(i)->GetEnemyControl()->FollowPlayer(true);
			enemies->at(i)->GetEnemyControl()->SetChaseDir(px - x, py - y);
		}
		else {
			enemies->at(i)->GetEnemyControl()->FollowPlayer(false);
		}
		
	}
	return damaged;
	
}