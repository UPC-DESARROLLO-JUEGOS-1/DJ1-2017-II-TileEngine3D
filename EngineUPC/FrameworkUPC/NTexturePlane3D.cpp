#include "NTexturePlane3D.h"

#include "GameFramework.h"
#include "ShaderManager.h"
#include "PrimitiveShaderColor3D.h"
#include "dtPositionNormalUVVertex.h"
#include "TexturedShader3D.h"

void NTexturePlane3D::SetColor(NColor color) {
	mColor = color;
}

void NTexturePlane3D::Initialize(float x, float y, float z,
	float sizeX, float sizeY, const std::string path)
{
	Drawable3D::Initialize(x, y, z);

	mSizeX = sizeX;
	mSizeY = sizeY;

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ShaderManager* shaderManagment = framework->GetShaderManager();
	ContentManager* contentManager = framework->GetContentManager();

	mContent = contentManager->LoadAndGetContent<ImageContent>(path);

	const std::string baseShaderPath = "Shaders/TexturedShader3D";
	mCurrentShader = (BaseShader*)shaderManagment->LoadAndGetShader<TexturedShader3D>(baseShaderPath);

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;

	dtPositionNormalUVVertex* vertexData = new dtPositionNormalUVVertex[4];
	// plane
	vertexData[0].SetPositionAndUV(-hsx, -hsy, 0, 0, 0); // up-left-front
	vertexData[1].SetPositionAndUV(-hsx, hsy, 0, 0, 1);  // down-left-front
	vertexData[2].SetPositionAndUV(hsx, -hsy, 0, 1, 0);  // up-right-front
	vertexData[3].SetPositionAndUV(hsx, hsy, 0, 1, 1);   // down-right-front
	dtPositionNormalUVVertex::ProcessNormal(&vertexData[0], &vertexData[1], &vertexData[2], glm::vec3(1, -1, 1)); // normal
	dtPositionNormalUVVertex::ProcessNormal(&vertexData[1], &vertexData[3], &vertexData[2], glm::vec3(1, -1, 1)); // normal

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(float) * 2)) * 4;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// indices
	int indicesArraySize = 6 * 1; // 1 faces with (2 triangles = 3 each triangle = 6 indices)
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

void NTexturePlane3D::Draw(float dt) {
	mCurrentShader->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	// matrix
	GLuint cameraLocation = mCurrentShader->GetUniformLocation("camera");
	GLuint modelLocation = mCurrentShader->GetUniformLocation("model");

	// ambient color
	int ambientColorLocation = mCurrentShader->GetUniformLocation("ambientColor");
	glUniform4f(ambientColorLocation, 
		mColor.NormalizedR(),
		mColor.NormalizedG(), 
		mColor.NormalizedB(), 
		mColor.NormalizedA());

	// matrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &(worldMatrix[0][0]));
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(mRenderCamera->GetResultMatrix()[0][0]));

	// texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mContent->GetTextureId());

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(dtPositionNormalUVVertex),
		(void*)offsetof(dtPositionNormalUVVertex, dtPositionNormalUVVertex::Position));
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(dtPositionNormalUVVertex),
		(void*)offsetof(dtPositionNormalUVVertex, dtPositionNormalUVVertex::Normal));
	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(dtPositionNormalUVVertex),
		(void*)offsetof(dtPositionNormalUVVertex, dtPositionNormalUVVertex::UV));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);

	// Esto dibuja en Frame Buffer
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_DEPTH_TEST);

	mCurrentShader->Stop();
}