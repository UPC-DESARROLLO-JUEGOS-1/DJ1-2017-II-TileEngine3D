#pragma once

#include "Drawable3D.h"
#include "ImageContent.h"

class NTexturePlane3D : public Drawable3D
{
public:
	NTexturePlane3D() { Drawable3D::Drawable3D(); }
	~NTexturePlane3D() { Drawable3D::~Drawable3D(); }

	inline float GetSizeX() { return mSizeX; }
	inline float GetSizeY() { return mSizeY; }

	void SetColor(NColor color);

	void Initialize(float x, float y, float z, float sizeX, float sizeY, const std::string path);
	void Draw(float dt);

private:
	float mSizeX, mSizeY;
	ImageContent* mContent;
};

