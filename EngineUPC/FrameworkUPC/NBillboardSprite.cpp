#include "NBillboardSprite.h"

#include "GameFramework.h"
#include "ShaderManager.h"
#include "PrimitiveShaderColor3D.h"
#include "dtPrimitiveCubeVertex.h"
#include "PrimitiveShaderColor3D.h"

void NBillboardSprite::SetColor(NColor color) {
	mColor = color;

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPrimitiveCubeVertex* vertexData = new dtPrimitiveCubeVertex[4];

	GLubyte r = 255;
	GLubyte g = 0;
	GLubyte b = 0;
	GLubyte a = 255;

	// front face
	vertexData[0].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[1].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[2].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[3].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
																	 // normal
	vertexData[0].ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2]);
	vertexData[1].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);
	vertexData[2].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);
	vertexData[3].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 4;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NBillboardSprite::Initialize(float x, float y, float z,
	float sizeX, float sizeY, float sizeZ)
{
	Drawable3D::Initialize(x, y, z);

	mSizeX = sizeX;
	mSizeY = sizeY;
	mSizeZ = sizeZ;

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();

	const std::string baseShaderPath = "Shaders/BasicLightingShader";
	mCurrentShader = (BaseShader*)shaderManagment->LoadAndGetShader<PrimitiveShaderColor3D>(baseShaderPath);

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPrimitiveCubeVertex* vertexData = new dtPrimitiveCubeVertex[4];

	GLubyte r = mColor.r;
	GLubyte g = mColor.g;
	GLubyte b = mColor.b;
	GLubyte a = mColor.a;

	// front face
	vertexData[0].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[1].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[2].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[3].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	dtPrimitiveCubeVertex::ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2]); // normal
	dtPrimitiveCubeVertex::ProcessNormal(&vertexData[1], &vertexData[3], &vertexData[2]); // normal

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 4;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// indices
	int indicesArraySize = 6; // 6 faces with (2 triangles = 3 each triangle = 6 indices)
	unsigned int* indicesData = new unsigned int[indicesArraySize];
	// front face
	indicesData[0] = 0; indicesData[1] = 1; indicesData[2] = 2;
	indicesData[3] = 1; indicesData[4] = 3; indicesData[5] = 2;

	int indexDataSize = sizeof(int) * indicesArraySize;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(indicesData[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mIndicesCount = indicesArraySize;
}

void NBillboardSprite::Draw(float dt) {
	mCurrentShader->Use();

	glEnable(GL_DEPTH_TEST);

	// matrix
	GLuint cameraLocation = mCurrentShader->GetUniformLocation("camera");
	GLuint modelLocation = mCurrentShader->GetUniformLocation("model");
	GLuint cameraPositionLocation = mCurrentShader->GetUniformLocation("cameraPosition");

	// matrix
	glUniform3f(cameraPositionLocation, mRenderCamera->GetX(), mRenderCamera->GetY(), mRenderCamera->GetZ());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &(worldMatrix[0][0]));
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(mRenderCamera->GetResultMatrix()[0][0]));

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(dtPrimitiveCubeVertex),
		(void*)offsetof(dtPrimitiveCubeVertex, dtPrimitiveCubeVertex::Position));
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(dtPrimitiveCubeVertex),
		(void*)offsetof(dtPrimitiveCubeVertex, dtPrimitiveCubeVertex::Normal));
	// Color
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtPrimitiveCubeVertex),
		(void*)offsetof(dtPrimitiveCubeVertex, dtPrimitiveCubeVertex::Color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);

	// Esto dibuja en Frame Buffer
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glDisable(GL_DEPTH_TEST);

	mCurrentShader->Stop();
}