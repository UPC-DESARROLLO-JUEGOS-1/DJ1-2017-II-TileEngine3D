#pragma once

#include "ImageContent.h"
#include "Drawable2D.h"

#include <string>
enum {
	NORMAL = 0,
	HIGHLIGHTED = 1,
	PRESSED = 2
};
class Button : public Drawable2D
{
public:
	Button() :
		pivot(0.0f, 0.0f)
	{}
	~Button()
	{
		content = nullptr;
		Drawable2D::~Drawable2D();
	}

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetVisibleWidth() { return width*abs(scale.x); }
	int GetVisibleHeight() { return height*abs(scale.y); }
	ImageContent* GetImageContent() { return content; }

	void Initialize(float x, float y, const std::string path);
	void Update(float dt);
	void Draw(float dt);

	void eventHandler();
	bool mouseInside(int mx, int my);
	void SetColor(float r, float g, float b, float a);
	void SetPivot(float x, float y);
	void SetPivot(float value);

protected:
	int width, height;
	int r, g, b, a;
	int sceneIndex;
	ImageContent* content;
	Vector2 pivot;

	void BindData();	
};

