#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <AL\alut.h>
#include <string>
#include <functional>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	int GetScreenWidth() { screenWidth; }
	int GetScreenHeight() { screenHeight; }

	int Create(const std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);
	void AddInputListener(std::function<void(SDL_Event)> callback) { onInputCallback = callback; }
	void Update(float dt);
	int GetEventType();
	void Present();
public:
	SDL_Event evnt;
private:
	int screenWidth, screenHeight;
	SDL_Window* window;
	std::function<void(SDL_Event)> onInputCallback = nullptr;
	
	void ProcessInputs();	
};