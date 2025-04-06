#include "Game.h"
#include "SDL3_image/SDL_image.h"
#include "Sprite.h"
#include "ECS/Components/Components.h"

SDL_Renderer* Game::renderer = nullptr;
EntityManager* Game::entity_manager = nullptr;

Game::Game()
{

}

Game::~Game()
{
}

bool Game::Init(const char* window_title, const int xpos, const int ypos, const int width, const int height)
{
	SDL_Log("Initializing SDL subsystems: SDL_INIT_EVENTS, SDL_INIT_VIDEO, SDL_INIT_AUDIO...");
	bool sdl_init_result = SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (!sdl_init_result) {
		SDL_Log("SDL_Init error: %s", SDL_GetError());
		return false;
	}
	SDL_Log("SDL subsystems initialized!");

	SDL_Window* window = SDL_CreateWindow(window_title, width, height, NULL);
	if (window == nullptr) {
		SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
		return false;
	}
	this->window = window;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == nullptr) {
		SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
		return false;
	}
	this->renderer = renderer;
	
	SDL_SetWindowPosition(window, xpos, ypos);
	this->is_running = true;

	// ECS setup	START
	this->entity_manager = new EntityManager();

	Entity& entity = entity_manager->CreateEntity();
	entity.AddComponent<TransformComponent>(32, 32);
	entity.AddComponent<SpriteComponent>().LoadTexture("./Assets/Sprites/CharactersSpritesheet.png").SetSourceRect({32 * 6,32 * 6,32,32});

	SpriteComponent& sprite_component = entity.GetComponent<SpriteComponent>();
	sprite_component.SetScale(0.3);

	// ECS setup	END
	return true;
}

void Game::SetFullscreen(bool is_fullscreen)
{
	SDL_SetWindowFullscreen(this->window, is_fullscreen);
}

void Game::SetIcon(const char* icon_path)
{
	SDL_Surface* icon_surface = IMG_Load(icon_path);
	if (icon_surface == nullptr) {
		SDL_Log("Game:SetIcon error: %s", SDL_GetError());
		return;
	}

	SDL_SetWindowIcon(this->window, icon_surface);
	SDL_DestroySurface(icon_surface);
}

SDL_AppResult Game::HandleEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
	case SDL_EVENT_KEY_DOWN:
		switch (event->key.scancode) {
		case SDL_SCANCODE_ESCAPE:
			return SDL_APP_SUCCESS;

		default: break;
		}
	default: break;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::Update()
{
	// Calculate delta_time
	this->delta_time = (SDL_GetTicks() - last_tick) / 1000.0;
	last_tick = SDL_GetTicks();

	// Update all entities
	this->entity_manager->Refresh();
	this->entity_manager->Update(this->delta_time);

	//SDL_Log("FPS: %lf", 1/this->delta_time);
	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::Render()
{
	SDL_SetRenderDrawColor(this->renderer, 37, 37, 144, 255);
	SDL_RenderClear(this->renderer);

	this->entity_manager->Render();

	SDL_RenderPresent(this->renderer);
	return SDL_APP_CONTINUE;
}

void Game::Cleanup(SDL_AppResult result)
{
	delete entity_manager;
	this->is_running = false;

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();

	switch (result) {
	case SDL_APP_SUCCESS:
		SDL_Log("[SUCCESS] Game stopped!");
		break;
	case SDL_APP_FAILURE:
	default:
		SDL_Log("[FAIL] Game stopped!");
		break;
	}
}

bool Game::IsRunning()
{
	return this->is_running;
}
