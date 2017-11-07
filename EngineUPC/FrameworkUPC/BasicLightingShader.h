#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"

class BasicLightingShader : public BaseShader
{
public:
	BasicLightingShader() { BaseShader::BaseShader(); }
	~BasicLightingShader() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}
};
