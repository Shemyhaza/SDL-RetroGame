#pragma once

#include "RetroGame.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void drawTex(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};