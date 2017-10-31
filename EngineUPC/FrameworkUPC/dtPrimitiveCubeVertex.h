#pragma once

#include "VertexData.h"

struct dtPrimitiveCubeVertex
{
	V3 Position;
	Color Color;

	void SetPosition(float x, float y, float z) {
		Position.x = x;
		Position.y = y;
		Position.z = z;
	}

	void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		Color.r = r;
		Color.g = g;
		Color.b = b;
		Color.a = a;
	}
};