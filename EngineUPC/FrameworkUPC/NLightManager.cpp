#include "NLightManager.h"
#include "NBasicLight.h"

NLightManager::~NLightManager() {}

void NLightManager::Initialize() {
	CreateLight<NBasicLight>("default", 0, 0, 0);
}

template<typename T>
T* NLightManager::CreateLight(std::string name, float x, float y, float z) {
	T* result = nullptr;

	if (!ExistsLight(name)) {
		result = new NBasicLight(this);
		result->Initialize(name, x, y, z);

		mLights.insert(std::make_pair(name, result));
	}
	else {
		result = GetLigth<T>(name);
	}
	
	return result;
}

bool NLightManager::ExistsLight(std::string name) {
	bool result = false;

	std::map<std::string, NBaseLight*>::iterator it = mLights.find(name);
	NBaseLight* light = it != mLights.end() ? it->second : nullptr;
	result = light != nullptr;

	return result;
}

template<typename T>
T* NLightManager::GetLigth(const std::string name) {
	std::map<std::string, NBaseLight*>::iterator it = mLights.find(name);
	T* result = it != mLights.end() ? (T*)it->second : nullptr;
	return result;
}