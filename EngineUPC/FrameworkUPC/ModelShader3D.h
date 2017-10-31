#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"

class ModelShader3D : public BaseShader
{
public:
	ModelShader3D() { BaseShader::BaseShader(); }
	~ModelShader3D() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}
};
