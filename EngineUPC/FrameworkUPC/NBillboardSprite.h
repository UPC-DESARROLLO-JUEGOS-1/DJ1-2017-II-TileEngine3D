#pragma once
#include "Drawable3D.h"
class NBillboardSprite :
	public Drawable3D
{
public:
	NBillboardSprite() { Drawable3D::Drawable3D(); }
	~NBillboardSprite() { Drawable3D::~Drawable3D(); }

	inline float GetSizeX() { return mSizeX; }
	inline float GetSizeY() { return mSizeY; }
	inline float GetSizeZ() { return mSizeZ; }

	void SetColor(NColor color);

	void Initialize(float x, float y, float z, float sizeX,
		float sizeY, float sizeZ);
	void Draw(float dt);

private:
	float mSizeX, mSizeY, mSizeZ;
};

