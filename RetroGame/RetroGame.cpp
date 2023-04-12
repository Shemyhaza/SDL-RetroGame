#include "RetroGame.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

#include "ECS.h"
#include "Components.h"

GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

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

		player = new GameObject("assets/mainPlayer.bmp", 650, 320);
		enemy = new GameObject("assets/enemy_one.bmp", 0, 0);
		map = new Map();

		newPlayer.addComponent<PositionComponent>();

		isRunning = true;
		return isRunning;
	}
	else { 
		std::cout << "Cannot initialise SDL subsystems!.." << SDL_GetError() << std::endl;
		isRunning = false;
		return isRunning;
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

	player->updateObj();
	enemy->updateObj();
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}


void Game::render() {

	Uint32 currentTime = SDL_GetTicks();
	float deltaTime = currentTime - lastTime;
	std::cout << "LastTime: " << lastTime << std::endl;
	std::cout << "CurrentTime: " << currentTime << std::endl;
	std::cout << "DeltaTime: " << deltaTime << std::endl;

	const float speed = deltaTime; 

	SDL_RenderClear(renderer);
	map->drawMap();
	player->renderObj();
	enemy->renderObj();

	const uint8* state = SDL_GetKeyboardState(NULL);

	// Conversrtion from logical values to decimal
	int stateRight = state[SDL_SCANCODE_RIGHT] ? 1 : 0;
	int stateLeft = state[SDL_SCANCODE_LEFT] ? 1 : 0;
	int stateUp = state[SDL_SCANCODE_UP] ? 1 : 0;
	int stateDown = state[SDL_SCANCODE_DOWN] ? 1 : 0;

	/*
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
	*/
	SDL_RenderPresent(renderer);
	lastTime = currentTime;
}


void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned!.." << std::endl;
}
