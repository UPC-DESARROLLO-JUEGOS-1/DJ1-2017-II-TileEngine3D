#pragma once

#include "NBaseLight.h"
#include "NColor.h"
#include "NLightManager.h"

class NBasicLight : public NBaseLight
{
public:
	const float DEFAULT_ATTENUATION = 0.01f;
	const float DEFAULT_INTESITY = 1.0f;
	const NColor DEFAULT_LIGHT_COLOR = NColor::White;

	inline NColor GetLightColorRaw() { return mLightColorRaw; }
	inline glm::vec3 GetLigthColor() { return mLightColor; }
	inline float GetAttenuation() { return mAttenuation; }
	inline float GetIntensity() { return mIntensity; }

	void SetLightColor(NColor color) {
		mLightColorRaw = color;
		mLightColor.x = ((float)color.r) / 255.0f;
		mLightColor.y = ((float)color.g) / 255.0f;
		mLightColor.z = ((float)color.b) / 255.0f;
	}
	inline void SetAttenuation(float attenuation) { mAttenuation = attenuation; }
	inline void SetIntensity(float intensity) { mIntensity = intensity; }

	NBasicLight(NLightManager* manager);
	~NBasicLight();

	void Initialize(std::string name, float x, float y, float z);

protected:
	NColor mLightColorRaw;
	glm::vec3 mLightColor;
	float mIntensity;
	float mAttenuation;
};

