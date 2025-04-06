#pragma once

#include "SDL3/SDL.h"
#include "ECS/ECS.h"

static const char* DEFAULT_TITLE = "SDL3 Game";
static const int DEFAULT_XPOS = 200;
static const int DEFAULT_YPOS = 100;
static const int DEFAULT_WIDTH = 700;
static const int DEFAULT_HEIGHT = 500;

class Game
{
public:
	// Methods
	Game();
	~Game();

	bool Init(const char* window_title = DEFAULT_TITLE, const int xpos = DEFAULT_XPOS, const int ypos = DEFAULT_YPOS, const int width = DEFAULT_WIDTH, const int height = DEFAULT_HEIGHT);

	void SetFullscreen(bool is_fullscreen);
	void SetIcon(const char* icon_path);

	SDL_AppResult HandleEvent(SDL_Event* event);
	SDL_AppResult Update();
	SDL_AppResult Render();
	void Cleanup(SDL_AppResult result);

	bool IsRunning();

	// Attributes
	static SDL_Renderer* renderer;
	static EntityManager* entity_manager;

private:
	// Methods

	// Attributes
	SDL_Window* window = nullptr;

	bool is_running = false;

	Uint64 last_tick = SDL_GetTicks();
	double delta_time = 0;
};

