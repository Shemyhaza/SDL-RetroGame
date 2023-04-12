#pragma once
#include "RetroGame.h"

class GameObject {
	
private:
	int xPos;
	int yPos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void updateObj();
	void renderObj();
};