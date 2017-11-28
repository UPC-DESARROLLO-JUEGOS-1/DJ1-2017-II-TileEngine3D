#include "Button.h"
#include "GameFramework.h"
#include "SpriteShader.h"
#include "MathUtils.h"

void Button::SetColor(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	sceneIndex = -1;

	BindData();
}

void Button::SetPivot(float x, float y)
{
	pivot.x = MathUtils::Clamp(x, 0.0f, 1.0f);
	pivot.y = MathUtils::Clamp(y, 0.0f, 1.0f);
}

void Button::SetPivot(float value)
{
	pivot.x = pivot.y = MathUtils::Clamp(value, 0.0f, 1.0f);
}

void Button::Initialize(float x, float y, const std::string path)
{
	clickReleased = true;
	clicked = false;
	state = NORMAL;
	position = Vector2(x, y);

	if (vbo[0] == 0) {
		glGenBuffers(NSPRITES, vbo);
	}

	GameFramework* framework = GameFramework::GET_FRAMEWORK();
	ContentManager* contentManager = framework->GetContentManager();
	ShaderManager* shaderManager = framework->GetShaderManager();

	mCurrentShader = shaderManager->LoadAndGetShader<SpriteShader>("Shaders/SpriteShader");
	content = contentManager->LoadAndGetContent<ImageContent>(path);
	width = content->GetWidth();
	height = content->GetHeight()/NSPRITES;
	r = g = b = a = 255;

	BindData();
}


void Button::Update(float dt)
{
	if (needMatrixUpdate)
	{
		glm::mat4 result(1.0f);
		glm::vec3 translate(position.x, position.y, 0.0f);
		glm::vec3 scale(scale.x, scale.y, 0.0f);
		glm::vec3 rotation(0.0f, 0.0f, 1.0f);

		glm::vec3 pivotPos(width*pivot.x, height*pivot.y, 0.0f);

		result = glm::translate(result, translate);
		result = glm::translate(result, pivotPos);
		result = glm::scale(result, scale);
		result = glm::rotate(result, rotationZ, rotation);
		result = glm::translate(result, -pivotPos);

		worldMatrix = result;
		needMatrixUpdate = false;
	}
	EventHandler();
}

void Button::EventHandler() {

	int eType = GameFramework::GET_FRAMEWORK()->GetWindow()->GetEventType();
	if (MouseInside(GameFramework::GET_FRAMEWORK()->GetMouseX(), GameFramework::GET_FRAMEWORK()->GetMouseY())) {		
		if (prevState == SDL_MOUSEBUTTONDOWN) {
			highlightable = false;
		}
		switch (eType)
		{
		case SDL_MOUSEMOTION:
			if(highlightable)
				state = HIGHLIGHTED;
			break;
		case SDL_MOUSEBUTTONDOWN:
			state = PRESSED;
			clickReleased = false;
			break;
		case SDL_MOUSEBUTTONUP:
			if(!clickReleased){
				printf("\n CARGA DE NUEVA ESCENA \n");
				clicked = true;
				clickReleased = true;
			}

			state = NORMAL;
			break;
		default:
			state = NORMAL;
			break;
		}
		prevState = eType;
	}
	else {		
		clickReleased = true;
		highlightable = true;
		state = NORMAL;
	}
	
}

bool Button::isClicked() {
	return clicked;
}

bool Button::MouseInside(int mx, int my) {
	//Check if mouse is in button

	bool inside = true;
	//Mouse is left of the button
	if (mx < position.x)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (mx > position.x + width)
	{
		inside = false;
	}
	//Mouse above the button
	else if (my < position.y)
	{
		inside = false;
	}
	//Mouse below the button
	else if (my > position.y + height)
	{
		inside = false;
	}
	return inside;
}
void Button::Draw(float dt)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mCurrentShader->Use();
	GLuint wvpLocation = mCurrentShader->GetUniformLocation("wvp");
	glm::mat4 cameraMatrix = mRenderCamera->GetResultMatrix();
	glm::mat4 resultMatrix = cameraMatrix*worldMatrix;

	glUniformMatrix4fv(wvpLocation, 1, GL_FALSE, &(resultMatrix[0][0]));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, content->GetTextureId());

	glBindBuffer(GL_ARRAY_BUFFER, vbo[state]);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DataSpriteVertex), (void*)offsetof(DataSpriteVertex, DataSpriteVertex::Position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DataSpriteVertex), (void*)offsetof(DataSpriteVertex, DataSpriteVertex::Color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(DataSpriteVertex), (void*)offsetof(DataSpriteVertex, DataSpriteVertex::UV));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	mCurrentShader->Stop();
}

void Button::BindData()
{
	DataSpriteVertex vertexData[6]; //2 triangles=1 quad
									//triangle 1}
	for (int i = 0; i < NSPRITES; i++)
	{
		float offsetA = (1.0f / NSPRITES) * (i + 1);
		float offsetB = (1.0f / NSPRITES) * (i);
		vertexData[0].SetPosition(width, height);
		vertexData[0].SetColor(r, g, b, a);
		vertexData[0].SetUV(1.0f, offsetA);
		vertexData[1].SetPosition(0, height);
		vertexData[1].SetColor(r, g, b, a);
		vertexData[1].SetUV(0.0f, offsetA);
		vertexData[2].SetPosition(0, 0);
		vertexData[2].SetColor(r, g, b, a);
		vertexData[2].SetUV(0.0f, offsetB);
		//triangle 2
		vertexData[3].SetPosition(0, 0);
		vertexData[3].SetColor(r, g, b, a);
		vertexData[3].SetUV(0.0f, offsetB);
		vertexData[4].SetPosition(width, 0);
		vertexData[4].SetColor(r, g, b, a);
		vertexData[4].SetUV(1.0f, offsetB);
		vertexData[5].SetPosition(width, height);
		vertexData[5].SetColor(r, g, b, a);
		vertexData[5].SetUV(1.0f, offsetA);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	}
}
