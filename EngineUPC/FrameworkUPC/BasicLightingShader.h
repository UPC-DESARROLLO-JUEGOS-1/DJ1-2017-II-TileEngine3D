#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"
#include "NBasicLight.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class BasicLightingShader : public BaseShader
{
public:
	BasicLightingShader() { BaseShader::BaseShader(); }
	~BasicLightingShader() { BaseShader::~BaseShader(); }

	NBasicLight* GetLight0() { return mBasicLight0; }
	NBasicLight* GetLight1() { return mBasicLight1; }

	void OnReady() {
		BaseShader::OnReady();

		// material
		mMaterialShininessLocation = GetUniformLocation("materialShininess");
		mMaterialSpecularColoeLocation = GetUniformLocation("materialSpecularColor");
		mAmbientCoefficientLocation = GetUniformLocation("ambientCoefficient");

		// light0
		mLightPositionLocation0 = GetUniformLocation("light0.position");
		mLightColorLocation0 = GetUniformLocation("light0.color");
		mLightAttenuationLocation0 = GetUniformLocation("light0.attenuation");
		mLightIntensityLocation0 = GetUniformLocation("light0.intensity");

		// light1
		mLightPositionLocation1 = GetUniformLocation("light1.position");
		mLightColorLocation1 = GetUniformLocation("light1.color");
		mLightAttenuationLocation1 = GetUniformLocation("light1.attenuation");
		mLightIntensityLocation1 = GetUniformLocation("light1.intensity");
	}

	void SetLight0(std::string name) {
		GameFramework* framework = GameFramework::GET_FRAMEWORK();
		NLightManager* lightManagment = framework->GetLightManager();

		mBasicLight0 = lightManagment->CreateLight<NBasicLight>(name, 0, 0, 0);
	}

	void SetLight1(std::string name) {
		GameFramework* framework = GameFramework::GET_FRAMEWORK();
		NLightManager* lightManagment = framework->GetLightManager();

		mBasicLight1 = lightManagment->CreateLight<NBasicLight>(name, 0, 0, 0);
	}

	void Use() {
		BaseShader::Use();

		// material
		glUniform1f(mMaterialShininessLocation, 80.0f);
		glUniform3f(mMaterialSpecularColoeLocation, 1.0f, 1.0f, 1.0f);
		glUniform1f(mAmbientCoefficientLocation, 1.0f);

		// light0
		if (mBasicLight0 != nullptr) {
			glUniform3fv(mLightPositionLocation0, 1, glm::value_ptr(mBasicLight0->GetPosition()));
			glUniform3fv(mLightColorLocation0, 1, glm::value_ptr(mBasicLight0->GetLigthColor()));
			glUniform1f(mLightAttenuationLocation0, mBasicLight0->GetAttenuation());
			glUniform1f(mLightIntensityLocation0, mBasicLight0->GetIntensity());
		}

		// light1
		if (mBasicLight1 != nullptr) {
			glUniform3fv(mLightPositionLocation1, 1, glm::value_ptr(mBasicLight1->GetPosition()));
			glUniform3fv(mLightColorLocation1, 1, glm::value_ptr(mBasicLight1->GetLigthColor()));
			glUniform1f(mLightAttenuationLocation1, mBasicLight1->GetAttenuation());
			glUniform1f(mLightIntensityLocation1, mBasicLight1->GetIntensity());
		}
	}

protected:
	NBasicLight* mBasicLight0;
	NBasicLight* mBasicLight1;

	// material
	GLuint mMaterialShininessLocation;
	GLuint mMaterialSpecularColoeLocation;
	GLuint mAmbientCoefficientLocation;

	// light0
	GLuint mLightPositionLocation0;
	GLuint mLightColorLocation0;
	GLuint mLightAttenuationLocation0;
	GLuint mLightIntensityLocation0;

	// light1
	GLuint mLightPositionLocation1;
	GLuint mLightColorLocation1;
	GLuint mLightAttenuationLocation1;
	GLuint mLightIntensityLocation1;

	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}
};
