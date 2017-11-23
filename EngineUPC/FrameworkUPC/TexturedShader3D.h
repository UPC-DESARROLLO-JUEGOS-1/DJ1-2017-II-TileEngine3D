#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"
#include "GameFramework.h"

#include <glm\glm.hpp>

class TexturedShader3D : public BaseShader
{
public:
	TexturedShader3D() { BaseShader::BaseShader(); }
	~TexturedShader3D() { BaseShader::~BaseShader(); }

	int GetAmbientColorLocation() { return mAmbientColorLocation; }

	void Use() {
		BaseShader::Use();
	}

protected:
	int mAmbientColorLocation;

	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}

	void OnReady() {
		BaseShader::OnReady();

		mAmbientColorLocation = GetUniformLocation("ambientColor");
	}
};
