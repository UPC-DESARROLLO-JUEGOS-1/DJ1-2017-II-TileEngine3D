#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"

class ModelPrimitiveShader3D : public BaseShader
{
public:
	ModelPrimitiveShader3D() { BaseShader::BaseShader(); }
	~ModelPrimitiveShader3D() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
		AddAttribute("vertexNormal");
		AddAttribute("vertexUV");
	}
};
