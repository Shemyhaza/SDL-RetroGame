#include "RetroGame.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	
	game = new Game();

	game->init("RetroSraka", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1500, 900, false);

	while (game->running()) {

		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();

	return 0;
}