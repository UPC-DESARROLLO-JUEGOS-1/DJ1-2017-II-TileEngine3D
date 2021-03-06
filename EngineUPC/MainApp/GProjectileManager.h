#pragma once

#include <vector>
#include "GBaseProjectile.h"
#include <GWorld.h>
class GameScene;

class GProjectileManager
{
public:
	GProjectileManager(GEngine* engine) { mEngine = engine; }
	~GProjectileManager()
	{
		for each (GBaseProjectile* projectile in mProjectileGroup) { delete projectile; }
	}

	void Initialize();
	void Update(float dt);
	void Draw(float dt);

	void CreateProjectile(float x, float y, float angle, float strength);
	std::vector<GBaseProjectile*>* GetProjectiles() { return &mProjectileGroup; }

private:
	std::vector<GBaseProjectile*> mProjectileGroup;
	GEngine * mEngine;
	GWorld * mWorld;
};

