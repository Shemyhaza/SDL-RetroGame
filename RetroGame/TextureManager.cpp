#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tmpSurface = IMG_Load(texture);
	if (tmpSurface == nullptr) {
		std::cout << "Cannot load surface!.." << SDL_GetError() << std::endl;
	}
	else { std::cout << "Surface loaded!.." << std::endl; }

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	if (tex == nullptr) {
		std::cout << "Cannot create Texture from surface!.." << SDL_GetError() << std::endl;
	}
	else { std::cout << "Textures loaded!.." << std::endl; }
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::drawTex(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}