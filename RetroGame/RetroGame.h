#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

typedef unsigned __int8 uint8;

class Game {

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* mainSpiritSurf = nullptr;
	SDL_Surface* mapSurf = nullptr;
	SDL_Texture* spiritTxt = nullptr;
	SDL_Texture* mapTxt = nullptr;

	bool isRunning = false;
	uint32_t lastTime = 0;
	int count = 0;

public:
	Game();
	~Game();

	bool init(const char* title, int xPos, int yPos, int width, int height, bool flag);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
};


