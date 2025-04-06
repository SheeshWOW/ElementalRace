#pragma once

#include <SDL3/SDL.h>
#include "../ECS.h"
#include "Components.h" // <!> ноюямн, бнглнфмю аеяйнмевмюъ пейспяхъ <!>

class SpriteComponent : public Component
{
public:
    // Methods
    SpriteComponent();
    ~SpriteComponent();

    SpriteComponent& LoadTexture(const char* texture_path);

    void Init() override;
    void Update(double delta_time) override;
    void Render() override;

    void SetSourceRect(const SDL_FRect& src_rect);
    void SetColor(const SDL_Color& color);
    void SetFlipMode(const SDL_FlipMode& flip_mode);
    void SetVisible(bool is_visible);

    bool IsVisible();

    // Attributes
    TransformComponent* transform = nullptr;
    SDL_Texture* texture = nullptr;

    SDL_FRect src_rect = { 0, 0, 0, 0 };
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_FlipMode flip_mode = SDL_FLIP_NONE;

    bool is_visible = true;
};

