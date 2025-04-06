#include "Sprite.h"
#include "TextureManager.h"

Sprite::Sprite(const char* texture_path, const SDL_FRect& srcRect, double xpos, double ypos)
{
	LoadTexture(texture_path);
	SetSourceRect(srcRect);
	SetPosition(xpos, ypos);
}

Sprite::~Sprite()
{
}

void Sprite::LoadTexture(const char* texture_path)
{
	this->texture = TextureManager::LoadTexture(texture_path);
	SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_NEAREST);
	SDL_GetTextureSize(this->texture, &this->destRect.w, &this->destRect.h);
}

void Sprite::HandleEvent(SDL_Event* event)
{
}

void Sprite::Update(double delta_time)
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) {
		this->destRect.y -= 1;
	}
	if (keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
		this->destRect.y += 1;
	}

	if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
		this->destRect.x -= 1;
	}
	if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
		this->destRect.x += 1;
	}
}

void Sprite::RenderTexture()
{
	if (!is_visible || !texture) return;
	SDL_FRect scaledDestRect = { this->destRect.x, this->destRect.y, this->destRect.w * scaleX, this->destRect.h * scaleY };

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);
	
	SDL_RenderTextureRotated(
		Game::renderer,
		this->texture,
		&this->srcRect,
		&scaledDestRect,
		this->rotation,
		nullptr,
		this->flip
	);

	// Debug

	//SDL_RenderTexture(this->renderer, this->texture, &this->srcRect, &scaledDestRect);
	//SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
}

void Sprite::Render()
{
	RenderTexture();
}

void Sprite::SetPosition(double x, double y)
{
	this->destRect.x = x;
	this->destRect.y = y;
}

void Sprite::SetSourceRect(const SDL_FRect& srcRect)
{
	this->srcRect = srcRect;
}

void Sprite::SetScale(double scaleX, double scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

void Sprite::SetScale(double scale)
{
	this->scaleX = this->scaleY = scale;
}

void Sprite::SetVisible(bool is_visible)
{
	this->is_visible = is_visible;
}

void Sprite::SetRotation(double rotation)
{
	this->rotation = rotation;
}

SDL_FRect Sprite::GetRect()
{
	return this->destRect;
}

bool Sprite::IsVisible()
{
	return this->is_visible;
}

void Sprite::SetColor(const SDL_Color& color)
{
	this->color = color;
}

void Sprite::SetFlipMode(const SDL_FlipMode& flip_mode)
{
	this->flip = flip_mode;
}
