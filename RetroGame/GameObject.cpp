#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {
	
	objTexture = TextureManager::LoadTexture(textureSheet);
	
	xPos = x;
	yPos = y;
}


void GameObject::updateObj() {

	xPos++;
	yPos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xPos;
	destRect.y = yPos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}


void GameObject::renderObj() {

	SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}