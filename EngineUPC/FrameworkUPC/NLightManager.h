#pragma once

#include <string>
#include <map>

#include "NBaseLight.h"

class GameFramework;

class NLightManager
{
public:
	NLightManager(GameFramework* framework) { mFramework = framework; }
	~NLightManager();

	void Initialize();
	bool ExistsLight(std::string name);


	template<typename T>
	T* CreateLight(std::string name, float x, float y, float z);
	template<typename T>
	T* GetLigth(const std::string name);

private:
	GameFramework* mFramework;
	std::map<std::string, NBaseLight*> mLights;
};

