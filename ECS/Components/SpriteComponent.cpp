#include "SpriteComponent.h"
#include "../../TextureManager.h"


SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent()
{
}

SpriteComponent& SpriteComponent::LoadTexture(const char* texture_path)
{
	this->texture = TextureManager::LoadTexture(texture_path);
	SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_NEAREST);

	if (this->entity->HasComponent<TransformComponent>()) {
		SDL_GetTextureSize(this->texture, &this->transform->scale.x, &this->transform->scale.y);
	}
	
	return *this;
}

void SpriteComponent::Init()
{
	this->transform = &this->entity->GetComponent<TransformComponent>();
}

void SpriteComponent::Update(double delta_time)
{
	//this->transform->Scale(delta_time * 25, 0);
	//this->transform->Translate(25 * delta_time, 25 * delta_time);

	const bool* keys = SDL_GetKeyboardState(NULL);
	Vector2D movement_direction_vec(0, 0);
	if (keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) {
		movement_direction_vec.y = -1;
	}
	if (keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
		movement_direction_vec.y = 1;
	}

	if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
		movement_direction_vec.x = -1;
	}
	if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
		movement_direction_vec.x = 1;
	}

	float direction_angle_rad = atan2(movement_direction_vec.y, movement_direction_vec.x);
	movement_direction_vec *= Vector2D(abs(cos(direction_angle_rad)), abs(sin(direction_angle_rad)));

	this->transform->Translate(movement_direction_vec * 25 * delta_time);
}

void SpriteComponent::Render()
{
	if (!is_visible || !texture) return;
	SDL_FRect scaled_dest_rect = { this->transform->position.x, this->transform->position.y, this->transform->scale.x * scaleX, this->transform->scale.y * scaleY };

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);

	SDL_RenderTextureRotated(
		Game::renderer,
		this->texture,
		&this->src_rect,
		&scaled_dest_rect,
		this->transform->rotation,
		nullptr,
		this->flip_mode
	);

	// Debug

	//SDL_RenderTexture(this->renderer, this->texture, &this->srcRect, &scaledDestRect);
	//SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
}

void SpriteComponent::SetSourceRect(const SDL_FRect& src_rect)
{
	this->src_rect = src_rect;
}

void SpriteComponent::SetColor(const SDL_Color& color)
{
	this->color = color;
}

void SpriteComponent::SetFlipMode(const SDL_FlipMode& flip_mode)
{
	this->flip_mode = flip_mode;
}

void SpriteComponent::SetScale(double scaleX, double scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

void SpriteComponent::SetScale(double scale)
{
	this->scaleX = this->scaleY = scale;
}

void SpriteComponent::SetVisible(bool is_visible)
{
	this->is_visible = is_visible;
}

bool SpriteComponent::IsVisible()
{
	return this->is_visible;
}
