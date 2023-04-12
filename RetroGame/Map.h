#pragma once
#include "RetroGame.h"

class Map {

private:
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[28][50];

public:
	Map();
	~Map();

	void loadMap(int arr[28][50]);
	void drawMap();
};

