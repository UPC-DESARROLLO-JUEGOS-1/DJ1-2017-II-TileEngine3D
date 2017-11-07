#include "NPrimitiveCube3D.h"

#include "GameFramework.h"
#include "ShaderManager.h"
#include "PrimitiveShaderColor3D.h"
#include "dtPrimitiveCubeVertex.h"
#include "BasicLightingShader.h"

struct Light {
	glm::vec3 position;
	glm::vec3 intensities; //a.k.a. the color of the light
	float attenuation;
	float ambientCoefficient;
};

void NPrimitiveCube3D::SetColor(NColor color) {
	mColor = color;

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPrimitiveCubeVertex* vertexData = new dtPrimitiveCubeVertex[24];

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
	vertexData[0].ProcessNormal(vertexData[0], vertexData[1], vertexData[2]);
	vertexData[1].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);
	vertexData[2].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);
	vertexData[3].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);

	//left face
	vertexData[4].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[5].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[6].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[7].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
																	// normal
	vertexData[4].ProcessNormal(vertexData[4], vertexData[5], vertexData[6]);
	vertexData[5].SetNormal(vertexData[4].Normal.x, vertexData[4].Normal.y, vertexData[4].Normal.z);
	vertexData[6].SetNormal(vertexData[4].Normal.x, vertexData[4].Normal.y, vertexData[4].Normal.z);
	vertexData[7].SetNormal(vertexData[4].Normal.x, vertexData[4].Normal.y, vertexData[4].Normal.z);

	// right face
	vertexData[8].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[9].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[10].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[11].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
																	// normal
	vertexData[8].ProcessNormal(vertexData[8], vertexData[9], vertexData[10]);
	vertexData[9].SetNormal(vertexData[8].Normal.x, vertexData[8].Normal.y, vertexData[8].Normal.z);
	vertexData[10].SetNormal(vertexData[8].Normal.x, vertexData[8].Normal.y, vertexData[8].Normal.z);
	vertexData[11].SetNormal(vertexData[8].Normal.x, vertexData[8].Normal.y, vertexData[8].Normal.z);

	// back face
	vertexData[12].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[13].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[14].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[15].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
																	// normal
	vertexData[12].ProcessNormal(vertexData[12], vertexData[13], vertexData[14]);
	vertexData[13].SetNormal(vertexData[12].Normal.x, vertexData[12].Normal.y, vertexData[12].Normal.z);
	vertexData[14].SetNormal(vertexData[12].Normal.x, vertexData[12].Normal.y, vertexData[12].Normal.z);
	vertexData[15].SetNormal(vertexData[12].Normal.x, vertexData[12].Normal.y, vertexData[12].Normal.z);

	// top face
	vertexData[16].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[17].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[18].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[19].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
																	// normal
	vertexData[16].ProcessNormal(vertexData[16], vertexData[17], vertexData[18]);
	vertexData[17].SetNormal(vertexData[16].Normal.x, vertexData[16].Normal.y, vertexData[16].Normal.z);
	vertexData[18].SetNormal(vertexData[16].Normal.x, vertexData[16].Normal.y, vertexData[16].Normal.z);
	vertexData[19].SetNormal(vertexData[16].Normal.x, vertexData[16].Normal.y, vertexData[16].Normal.z);

	// bottom face
	vertexData[20].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[21].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[22].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[23].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
																	// normal
	vertexData[20].ProcessNormal(vertexData[20], vertexData[21], vertexData[22]);
	vertexData[21].SetNormal(vertexData[20].Normal.x, vertexData[20].Normal.y, vertexData[20].Normal.z);
	vertexData[22].SetNormal(vertexData[20].Normal.x, vertexData[20].Normal.y, vertexData[20].Normal.z);
	vertexData[23].SetNormal(vertexData[20].Normal.x, vertexData[20].Normal.y, vertexData[20].Normal.z);

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 24;

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

	const std::string baseShaderPath = "Shaders/BasicLightingShader";
	mCurrentShader = (BaseShader*)shaderManagment->LoadAndGetShader<BasicLightingShader>(baseShaderPath);

	float hsx = mSizeX / 2.0f;
	float hsy = mSizeY / 2.0f;
	float hsz = mSizeZ / 2.0f;

	dtPrimitiveCubeVertex* vertexData = new dtPrimitiveCubeVertex[24];

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
	vertexData[0].ProcessNormal(vertexData[0], vertexData[1], vertexData[2]);
	vertexData[1].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);
	vertexData[2].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);
	vertexData[3].SetNormal(vertexData[0].Normal.x, vertexData[0].Normal.y, vertexData[0].Normal.z);

	//left face
	vertexData[4].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[5].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[6].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[7].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
																	// normal
	vertexData[4].ProcessNormal(vertexData[4], vertexData[5], vertexData[6]);
	vertexData[5].SetNormal(vertexData[4].Normal.x, vertexData[4].Normal.y, vertexData[4].Normal.z);
	vertexData[6].SetNormal(vertexData[4].Normal.x, vertexData[4].Normal.y, vertexData[4].Normal.z);
	vertexData[7].SetNormal(vertexData[4].Normal.x, vertexData[4].Normal.y, vertexData[4].Normal.z);

	// right face
	vertexData[8].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[9].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[10].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[11].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
																	// normal
	vertexData[8].ProcessNormal(vertexData[8], vertexData[9], vertexData[10]);
	vertexData[9].SetNormal(vertexData[8].Normal.x, vertexData[8].Normal.y, vertexData[8].Normal.z);
	vertexData[10].SetNormal(vertexData[8].Normal.x, vertexData[8].Normal.y, vertexData[8].Normal.z);
	vertexData[11].SetNormal(vertexData[8].Normal.x, vertexData[8].Normal.y, vertexData[8].Normal.z);

	// back face
	vertexData[12].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[13].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[14].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
	vertexData[15].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
																	// normal
	vertexData[12].ProcessNormal(vertexData[12], vertexData[13], vertexData[14]);
	vertexData[13].SetNormal(vertexData[12].Normal.x, vertexData[12].Normal.y, vertexData[12].Normal.z);
	vertexData[14].SetNormal(vertexData[12].Normal.x, vertexData[12].Normal.y, vertexData[12].Normal.z);
	vertexData[15].SetNormal(vertexData[12].Normal.x, vertexData[12].Normal.y, vertexData[12].Normal.z);

	// top face
	vertexData[16].SetPositionAndColor(-hsx, -hsy, -hsz, r, g, b, a); // up-left-front
	vertexData[17].SetPositionAndColor(hsx, -hsy, -hsz, r, g, b, a);  // up-right-front
	vertexData[18].SetPositionAndColor(-hsx, -hsy, hsz, r, g, b, a); // up-left-back
	vertexData[19].SetPositionAndColor(hsx, -hsy, hsz, r, g, b, a);	// up-right-back
																	// normal
	vertexData[16].ProcessNormal(vertexData[16], vertexData[17], vertexData[18]);
	vertexData[17].SetNormal(vertexData[16].Normal.x, vertexData[16].Normal.y, vertexData[16].Normal.z);
	vertexData[18].SetNormal(vertexData[16].Normal.x, vertexData[16].Normal.y, vertexData[16].Normal.z);
	vertexData[19].SetNormal(vertexData[16].Normal.x, vertexData[16].Normal.y, vertexData[16].Normal.z);

	// bottom face
	vertexData[20].SetPositionAndColor(-hsx, hsy, -hsz, r, g, b, a);  // down-left-front
	vertexData[21].SetPositionAndColor(hsx, hsy, -hsz, r, g, b, a);   // down-right-front
	vertexData[22].SetPositionAndColor(-hsx, hsy, hsz, r, g, b, a);	// down-left-back
	vertexData[23].SetPositionAndColor(hsx, hsy, hsz, r, g, b, a);	// down-right-back
																	// normal
	vertexData[20].ProcessNormal(vertexData[20], vertexData[21], vertexData[22]);
	vertexData[21].SetNormal(vertexData[20].Normal.x, vertexData[20].Normal.y, vertexData[20].Normal.z);
	vertexData[22].SetNormal(vertexData[20].Normal.x, vertexData[20].Normal.y, vertexData[20].Normal.z);
	vertexData[23].SetNormal(vertexData[20].Normal.x, vertexData[20].Normal.y, vertexData[20].Normal.z);

	int size = ((sizeof(float) * 3) + (sizeof(float) * 3) + (sizeof(GLbyte) * 4)) * 24;

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
	indicesData[6] = 6; indicesData[7] = 7; indicesData[8] = 4;
	indicesData[9] = 7; indicesData[10] = 5; indicesData[11] = 4;
	// right face
	indicesData[12] = 8; indicesData[13] = 9; indicesData[14] = 10;
	indicesData[15] = 9; indicesData[16] = 11; indicesData[17] = 10;
	// back face
	indicesData[18] = 14; indicesData[19] = 15; indicesData[20] = 12;
	indicesData[21] = 15; indicesData[22] = 13; indicesData[23] = 12;
	// top face
	indicesData[24] = 18; indicesData[25] = 16; indicesData[26] = 19;
	indicesData[27] = 16; indicesData[28] = 17; indicesData[29] = 19;
	// bottom face
	indicesData[30] = 20; indicesData[31] = 22; indicesData[32] = 21;
	indicesData[33] = 22; indicesData[34] = 23; indicesData[35] = 21;

	int indexDataSize = sizeof(int) * indicesArraySize;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(indicesData[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	mIndicesCount = indicesArraySize;
}

void NPrimitiveCube3D::Draw(float dt) {
	mCurrentShader->Use();

	glEnable(GL_DEPTH_TEST);

	Light gLight;
	gLight.position = glm::vec3(2, 0, -1);
	gLight.intensities = glm::vec3(1, 1, 1);
	gLight.attenuation = 0.01f;
	gLight.ambientCoefficient = 0.005f;

	// matrix
	GLuint cameraLocation = mCurrentShader->GetUniformLocation("camera");
	GLuint modelLocation = mCurrentShader->GetUniformLocation("model");
	GLuint cameraPositionLocation = mCurrentShader->GetUniformLocation("cameraPosition");

	// material
	GLuint materialShininessLocation = mCurrentShader->GetUniformLocation("materialShininess");
	GLuint materialSpecularColoeLocation = mCurrentShader->GetUniformLocation("materialSpecularColor");
	// light
	GLuint lightPositionLocation = mCurrentShader->GetUniformLocation("light.position");
	GLuint lightIntensitiesLocation = mCurrentShader->GetUniformLocation("light.intensities");
	GLuint lightAttenuationLocation = mCurrentShader->GetUniformLocation("light.attenuation");
	GLuint lightAmbientCoefficientLocation = mCurrentShader->GetUniformLocation("light.ambientCoefficient");

	// material
	glUniform1f(materialShininessLocation, 80.0f);
	glUniform3f(materialSpecularColoeLocation, 1.0f, 1.0f, 1.0f);
	// light
	glUniform3fv(lightPositionLocation, 1, glm::value_ptr(gLight.position));
	glUniform3fv(lightIntensitiesLocation, 1, glm::value_ptr(gLight.intensities));
	glUniform1f(lightAttenuationLocation, gLight.attenuation);
	glUniform1f(lightAmbientCoefficientLocation, gLight.ambientCoefficient);
	// matrix
	glUniform3f(cameraPositionLocation, mRenderCamera->GetX(), mRenderCamera->GetY(), mRenderCamera->GetZ());
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &(worldMatrix[0][0]));
	glUniformMatrix4fv(cameraLocation, 1, GL_FALSE, &(mRenderCamera->GetResultMatrix()[0][0]));

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(dtPrimitiveCubeVertex),
		(void*)offsetof(dtPrimitiveCubeVertex, Position));
	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(dtPrimitiveCubeVertex),
		(void*)offsetof(dtPrimitiveCubeVertex, Normal));
	// Color
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtPrimitiveCubeVertex),
		(void*)offsetof(dtPrimitiveCubeVertex, Color));



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);

	// Esto dibuja en Frame Buffer
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	glDisable(GL_DEPTH_TEST);

	mCurrentShader->Stop();
}