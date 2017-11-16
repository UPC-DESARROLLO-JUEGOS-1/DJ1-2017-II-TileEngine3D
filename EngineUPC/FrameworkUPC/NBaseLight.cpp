#include "NBaseLight.h"

void NBaseLight::Initialize(std::string name, float x, float y, float z) {
	mPosition = glm::vec3(x, y, z);
	mName = name;
}