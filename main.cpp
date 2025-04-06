#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Game.h"

static Game* game;

static const int MAX_FPS = 240;
static const int MAX_DELAY = 1000 / MAX_FPS;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) 
{
	game = new Game();

	bool game_init_result = game->Init("Elemental Race", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500);
	if (!game_init_result) {
		return SDL_APP_FAILURE;
	}

	game->SetFullscreen(false);
	game->SetIcon("./Assets/Icon.svg");

	return SDL_APP_CONTINUE;
};

SDL_AppResult SDL_AppIterate(void* appstate)
{
	Uint64 start_tick = SDL_GetTicks();

	SDL_AppResult update_result = game->Update();
	if (update_result != SDL_APP_CONTINUE) {
		return update_result;
	}
	SDL_AppResult render_result = game->Render();
	if (render_result != SDL_APP_CONTINUE) {
		return update_result;
	}

	Uint64 passed_ticks = SDL_GetTicks() - start_tick;
	if (MAX_DELAY > passed_ticks) {
		//SDL_Log("waiting: %ld", MAX_DELAY - (int)passed_ticks);
		SDL_Delay(MAX_DELAY-passed_ticks); // Limit FPS
	}

	return SDL_APP_CONTINUE;
};
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	return game->HandleEvent(event);
};

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	game->Cleanup(result);
	delete game;
};