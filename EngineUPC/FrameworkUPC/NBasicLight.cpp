#include "NBasicLight.h"

NBasicLight::NBasicLight(NLightManager* manager) 
	: NBaseLight(manager) {}
NBasicLight::~NBasicLight() {}

void NBasicLight::Initialize(std::string name, float x, float y, float z) {
	NBaseLight::Initialize(name, x, y, z);

	// set default values
	SetLightColor(NBasicLight::DEFAULT_LIGHT_COLOR);
	SetAttenuation(NBasicLight::DEFAULT_ATTENUATION);
	SetIntensity(NBasicLight::DEFAULT_INTESITY);
}
