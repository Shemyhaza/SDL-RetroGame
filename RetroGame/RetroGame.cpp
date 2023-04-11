#include "RetroGame.h"

SDL_Texture* playerTex = nullptr;
SDL_Texture* mapTex = nullptr;
SDL_Rect srcR, destR = { 650, 320, 64, 64 };

Game::Game() {}
Game::~Game() {}

bool Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen) {

	lastTime = SDL_GetTicks();
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Sucessfully initialised!.." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			std::cout << "Window created!.." << std::endl;
		}
		else { 
			std::cout << "Cannot create window!.." << SDL_GetError() << std::endl; 
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!.." << std::endl;
		}

		SDL_Surface* tmpSurface = IMG_Load("mainPlayer.bmp");
		SDL_Surface* tmpSurfaceB = IMG_Load("pixelArt.bmp");

		if (tmpSurface == nullptr || tmpSurfaceB == nullptr) {
			std::cout << "Cannot load surface!.." << SDL_GetError() << std::endl;
			return false;
		}
		else { std::cout << "Surface loaded!.." << std::endl; }

		playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		mapTex = SDL_CreateTextureFromSurface(renderer, tmpSurfaceB);

		if (playerTex == nullptr || mapTex == nullptr) {
			std::cout << "Cannot create Texture from surface!.." << SDL_GetError() << std::endl;
			return false;
		}
		else { std::cout << "Textures loaded!.." << std::endl; }
		SDL_FreeSurface(tmpSurfaceB);
		SDL_FreeSurface(tmpSurface);
		
		return isRunning = true;
	}
	else { 
		std::cout << "Cannot initialise SDL subsystems!.." << SDL_GetError() << std::endl;
		return isRunning = false; 
	}
}


void Game::handleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type) {

	case SDL_QUIT:
		isRunning = false;
		break;

	case SDL_KEYDOWN:
		if ((event.key.keysym.sym == SDLK_F4) && (event.key.keysym.mod & KMOD_ALT)) {
			isRunning = false;
		}
	default:
		break;
	}
}


void Game::update() {

}


void Game::render() {

	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = currentTime - lastTime;
	std::cout << "LastTime: " << lastTime << std::endl;
	std::cout << "CurrentTime: " << currentTime << std::endl;
	std::cout << "DeltaTime: " << deltaTime << std::endl;

	const float speed = deltaTime; 

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, mapTex, NULL, NULL);
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);

	const uint8* state = SDL_GetKeyboardState(NULL);

	// Conversrtion from logical values to decimal
	int stateRight = state[SDL_SCANCODE_RIGHT] ? 1 : 0;
	int stateLeft = state[SDL_SCANCODE_LEFT] ? 1 : 0;
	int stateUp = state[SDL_SCANCODE_UP] ? 1 : 0;
	int stateDown = state[SDL_SCANCODE_DOWN] ? 1 : 0;

	int stateValue = stateRight * 8 + stateLeft * 4 + stateUp * 2 + stateDown * 1; 
	switch (stateValue) {
	case 10:
		std::cout << "RIGHT_UP" << std::endl;
		destR.x += deltaTime;
		destR.y -= deltaTime;
		break;
	case 9:
		std::cout << "RIGHT_DOWN" << std::endl;
		destR.x += deltaTime;
		destR.y += deltaTime;
		break;
	case 8:
		std::cout << "RIGHT" << std::endl;
		destR.x += deltaTime;
		break;
	case 6:
		std::cout << "LEFT_UP" << std::endl;
		destR.x -= deltaTime;
		destR.y -= deltaTime;
		break;
	case 5:
		std::cout << "LEFT_DOWN" << std::endl;
		destR.x -= deltaTime;
		destR.y += deltaTime;
		break;
	case 4:
		std::cout << "LEFT" << std::endl;
		destR.x -= deltaTime;
		break;
	case 2:
		std::cout << "UP" << std::endl;
		destR.y -= deltaTime;
		break;
	case 1:
		std::cout << "DOWN" << std::endl;
		destR.y += deltaTime;
		break;
	default:
		break;
	}
	SDL_RenderPresent(renderer);
	lastTime = currentTime;
}


void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!.." << std::endl;
}
