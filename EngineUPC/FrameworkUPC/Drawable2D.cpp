#include "Drawable2D.h"

Drawable2D::Drawable2D() : 
	position(0.0f, 0.0f),
	scale(1.0f, 1.0f),
	rotationZ(0.0f)
{
}

Drawable2D::~Drawable2D()
{
	if (mVBO_ID != 0)
	{
		glDeleteBuffers(1, &mVBO_ID);
	}
}

void Drawable2D::Initialize(float x, float y)
{
	position = Vector2(x, y);

	if (mVBO_ID == 0)
	{
		glGenBuffers(1, &mVBO_ID);
	}
}
