#pragma once

#include "TB3D_Actor.h"

#include <FrameworkUPC\NTexturePlane3D.h>

class TB3D_Engine;

class TB3D_Entity :
	public TB3D_Actor
{
public:
	TB3D_Entity(TB3D_Engine* engine);
	~TB3D_Entity();

	void CreateCollision(float size);

	virtual void Initialize(std::string file);

	virtual void Update(float dt);
	virtual void Draw(float dt);

private:
	NTexturePlane3D* mPlane;
};

