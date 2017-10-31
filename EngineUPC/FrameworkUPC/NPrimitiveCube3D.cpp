#include "NPrimitiveCube3D.h"

#include "GameFramework.h"
#include "ShaderManager.h"
#include "PrimitiveShaderColor3D.h"
#include "dtPrimitiveCubeVertex.h"

void NPrimitiveCube3D::SetColor(NColor color) {
	mColor = color;

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPrimitiveCubeVertex* vertexData = new dtPrimitiveCubeVertex[8];
	// First face
	vertexData[0].SetPosition(-hsx, -hsy, -hsz);
	vertexData[1].SetPosition(-hsx, hsy, -hsz);
	vertexData[2].SetPosition(hsx, -hsy, -hsz);
	vertexData[3].SetPosition(hsx, hsy, -hsz);
	// Second face
	vertexData[4].SetPosition(-hsx, -hsy, hsz);
	vertexData[5].SetPosition(-hsx, hsy, hsz);
	vertexData[6].SetPosition(hsx, -hsy, hsz);
	vertexData[7].SetPosition(hsx, hsy, hsz);

	// colors
	vertexData[0].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[1].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[2].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[3].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[4].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[5].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[6].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[7].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);

	int size = ((sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 8;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NPrimitiveCube3D::Initialize(float x, float y, float z,
	float sizeX, float sizeY, float sizeZ)
{
	Drawable3D::Initialize(x, y, z);

	mSizeX = sizeX;
	mSizeY = sizeY;
	mSizeZ = sizeZ;

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();

	const std::string baseShaderPath = "Shaders/PrimitiveShaderColor3D";
	mCurrentShader = (BaseShader*)shaderManagment->LoadAndGetShader<PrimitiveShaderColor3D>(baseShaderPath);

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPrimitiveCubeVertex* vertexData = new dtPrimitiveCubeVertex[8];
	// First face
	vertexData[0].SetPosition(-hsx, -hsy, -hsz);
	vertexData[1].SetPosition(-hsx, hsy, -hsz);
	vertexData[2].SetPosition(hsx, -hsy, -hsz);
	vertexData[3].SetPosition(hsx, hsy, -hsz);
	// Second face
	vertexData[4].SetPosition(-hsx, -hsy, hsz);
	vertexData[5].SetPosition(-hsx, hsy, hsz);
	vertexData[6].SetPosition(hsx, -hsy, hsz);
	vertexData[7].SetPosition(hsx, hsy, hsz);

	// colors
	vertexData[0].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[1].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[2].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[3].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[4].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[5].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[6].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	vertexData[7].SetColor(mColor.r, mColor.g, mColor.b, mColor.a);

	int size = ((sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 8;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// indices
	int indicesArraySize = 6 * 6; // 6 faces with (2 triangles = 3 each triangle = 6 indices)
	unsigned int* indicesData = new unsigned int[indicesArraySize];
	// front face
	indicesData[0] = 0; indicesData[1] = 1; indicesData[2] = 2;
	indicesData[3] = 1; indicesData[4] = 3; indicesData[5] = 2;
	// left face
	indicesData[6] = 4; indicesData[7] = 5; indicesData[8] = 0;
	indicesData[9] = 5; indicesData[10] = 1; indicesData[11] = 0;
	// right face
	indicesData[12] = 2; indicesData[13] = 3; indicesData[14] = 6;
	indicesData[15] = 3; indicesData[16] = 7; indicesData[17] = 6;
	// back face
	indicesData[18] = 6; indicesData[19] = 7; indicesData[20] = 4;
	indicesData[21] = 7; indicesData[22] = 5; indicesData[23] = 4;
	// top face
	indicesData[24] = 4; indicesData[25] = 0; indicesData[26] = 6;
	indicesData[27] = 0; indicesData[28] = 2; indicesData[29] = 6;
	// bottom face
	indicesData[30] = 1; indicesData[31] = 5; indicesData[32] = 3;
	indicesData[33] = 5; indicesData[34] = 7; indicesData[35] = 3;

	int indexDataSize = sizeof(int) * indicesArraySize;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(indicesData[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mIndicesCount = indicesArraySize;
}

void NPrimitiveCube3D::Draw(float dt) {
	mCurrentShader->Use();

	glEnable(GL_DEPTH_TEST);

	GLuint mvpLocation = mCurrentShader->GetUniformLocation("wvp");
	glm::mat4 cameraMatrix = mRenderCamera->GetResultMatrix();
	glm::mat4 resultMatrix = cameraMatrix * worldMatrix;

	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(resultMatrix[0][0]));

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(dtPrimitiveCubeVertex), (void*)offsetof(dtPrimitiveCubeVertex, dtPrimitiveCubeVertex::Position));
	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtPrimitiveCubeVertex), (void*)offsetof(dtPrimitiveCubeVertex, dtPrimitiveCubeVertex::Color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);

	// Esto dibuja en Frame Buffer
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glDisable(GL_DEPTH_TEST);

	mCurrentShader->Stop();
}