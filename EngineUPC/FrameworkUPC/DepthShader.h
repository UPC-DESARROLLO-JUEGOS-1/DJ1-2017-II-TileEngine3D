#pragma once

#include "BaseShader.h"
#include "VertexData.h"
#include "Vector2.h"

class DepthShader : public BaseShader
{
public:
	DepthShader() { BaseShader::BaseShader(); }
	~DepthShader() { BaseShader::~BaseShader(); }

protected:
	void CreateAttributes()
	{
		AddAttribute("vertexPosition");
	}
};


