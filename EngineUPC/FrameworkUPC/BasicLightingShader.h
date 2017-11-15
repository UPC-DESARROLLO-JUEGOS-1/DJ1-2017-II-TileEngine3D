#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"
#include "NBasicLight.h"
#include "GameFramework.h"
#include "EnumLightType.h"

#include <glm\glm.hpp>

class BasicLightingShader : public BaseShader
{
public:
	BasicLightingShader() { BaseShader::BaseShader(); }
	~BasicLightingShader() { BaseShader::~BaseShader(); }

	NBasicLight* GetLight0() { return mBasicLight0; }
	NBasicLight* GetLight1() { return mBasicLight1; }

	void SetLight0(std::string name, EnumLightType lightType) {
		GameFramework* framework = GameFramework::GET_FRAMEWORK();
		NLightManager* lightManagment = framework->GetLightManager();

		switch (lightType) {
		case EnumLightType::DIRECTIONAL_LIGHT:
			mBasicLight0 = lightManagment->CreateDirectionalLight(name, 0, 0, 0);
			break;
		case EnumLightType::SPOT_LIGHT:
			glm::vec3 position;
			position.x = 0;
			position.y = 0;
			position.z = 0;

			glm::vec3 coneDirection;
			coneDirection.x = 0;
			coneDirection.y = 0;
			coneDirection.z = 0;

			float coneAngle = 0;

			mBasicLight0 = lightManagment->CreateSpotLight(name, position, 
				coneDirection, coneAngle);
			break;
		}
	}

	void SetLight1(std::string name, EnumLightType lightType) {
		GameFramework* framework = GameFramework::GET_FRAMEWORK();
		NLightManager* lightManagment = framework->GetLightManager();

		switch (lightType) {
		case EnumLightType::DIRECTIONAL_LIGHT:
			mBasicLight1 = lightManagment->CreateDirectionalLight(name, 0, 0, 0);
			break;
		case EnumLightType::SPOT_LIGHT:
			glm::vec3 position;
			position.x = 0;
			position.y = 0;
			position.z = 0;

			glm::vec3 coneDirection;
			coneDirection.x = 0;
			coneDirection.y = 0;
			coneDirection.z = 0;

			float coneAngle = 0;

			mBasicLight1 = lightManagment->CreateSpotLight(name, position,
				coneDirection, coneAngle);
			break;
		}
	}

	void Use() {
		BaseShader::Use();

		// material
		glUniform1f(mMaterialShininessLocation, 80.0f);
		glUniform3f(mMaterialSpecularColoeLocation, 1.0f, 1.0f, 1.0f);

		// light0
		if (mBasicLight0 != nullptr) {
			glUniform4fv(mLightPositionLocation0, 1, glm::value_ptr(mBasicLight0->GetPosition()));
			glUniform3fv(mLightColorLocation0, 1, glm::value_ptr(mBasicLight0->GetLigthColor()));
			glUniform1f(mLightAttenuationLocation0, mBasicLight0->GetAttenuation());
			glUniform1f(mLightAmbientCoefficientLocation0, mBasicLight0->GetAmbientCoefficient());
			glUniform1f(mLightConeAngleLocation0, mBasicLight0->GetConeAngle());
			glUniform3fv(mLightConeDirectionLocation0, 1, glm::value_ptr(mBasicLight0->GetConeDirection()));
		}

		// light1
		if (mBasicLight1 != nullptr) {
			glUniform4fv(mLightPositionLocation1, 1, glm::value_ptr(mBasicLight1->GetPosition()));
			glUniform3fv(mLightColorLocation1, 1, glm::value_ptr(mBasicLight1->GetLigthColor()));
			glUniform1f(mLightAttenuationLocation1, mBasicLight1->GetAttenuation());
			glUniform1f(mLightAmbientCoefficientLocation1, mBasicLight1->GetAmbientCoefficient());
			glUniform1f(mLightConeAngleLocation1, mBasicLight1->GetConeAngle());
			glUniform3fv(mLightConeDirectionLocation1, 1, glm::value_ptr(mBasicLight1->GetConeDirection()));
		}
	}

protected:
	NBasicLight* mBasicLight0;
	NBasicLight* mBasicLight1;

	// material
	GLuint mMaterialShininessLocation;
	GLuint mMaterialSpecularColoeLocation;

	// light0
	GLuint mLightPositionLocation0;
	GLuint mLightColorLocation0;
	GLuint mLightAttenuationLocation0;
	GLuint mLightAmbientCoefficientLocation0;
	GLuint mLightConeAngleLocation0;
	GLuint mLightConeDirectionLocation0;

	// light1
	GLuint mLightPositionLocation1;
	GLuint mLightColorLocation1;
	GLuint mLightAttenuationLocation1;
	GLuint mLightAmbientCoefficientLocation1;
	GLuint mLightConeAngleLocation1;
	GLuint mLightConeDirectionLocation1;

	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}

	void OnReady() {
		BaseShader::OnReady();

		// material
		mMaterialShininessLocation = GetUniformLocation("materialShininess");
		mMaterialSpecularColoeLocation = GetUniformLocation("materialSpecularColor");
		
		// light0
		mLightPositionLocation0 = GetUniformLocation("light0.position");
		mLightColorLocation0 = GetUniformLocation("light0.intensities");
		mLightAttenuationLocation0 = GetUniformLocation("light0.attenuation");
		mLightAmbientCoefficientLocation0 = GetUniformLocation("light0.ambientCoefficient");
		mLightConeAngleLocation0 = GetUniformLocation("light0.coneAngle");
		mLightConeDirectionLocation0 = GetUniformLocation("light0.coneDirection");

		// light1
		mLightPositionLocation1 = GetUniformLocation("light1.position");
		mLightColorLocation1 = GetUniformLocation("light1.intensities");
		mLightAttenuationLocation1 = GetUniformLocation("light1.attenuation");
		mLightAmbientCoefficientLocation1 = GetUniformLocation("light1.ambientCoefficient");
		mLightConeAngleLocation1 = GetUniformLocation("light1.coneAngle");
		mLightConeDirectionLocation1 = GetUniformLocation("light1.coneDirection");
	}
};
