#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "BaseShader.h"
#include "BaseCamera.h"

class NBaseDrawable
{
public:
	NBaseDrawable();
	~NBaseDrawable();

	GLuint GetVBO_Id() { return mVBO_ID; }
	GLuint GetIBO_Id() { return mIBO_ID; }
	glm::mat4 GetWorldMatrix() { return worldMatrix; }

	virtual void Update(float dt) {}
	virtual void Draw(float dt) {}

protected:
	GLuint mVBO_ID;
	GLuint mIBO_ID;

	glm::mat4 worldMatrix;
	bool needMatrixUpdate;

	BaseShader* mCurrentShader;
	BaseCamera* mRenderCamera;
};

