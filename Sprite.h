#pragma once

#include <SDL3/SDL.h>
#include "Game.h"

class Sprite {
public:
    // Methods
    Sprite(const char* texture_path, const SDL_FRect& srcRect = {0, 0, 32, 32}, double xpos = 0, double ypos = 0);
    virtual ~Sprite();

    void LoadTexture(const char* texture_path);

    virtual void HandleEvent(SDL_Event* event);
    virtual void Update(double delta_time);
    void RenderTexture();
    virtual void Render();

    void SetSourceRect(const SDL_FRect& srcRect);
    void SetColor(const SDL_Color& color);
    void SetFlipMode(const SDL_FlipMode& flip_mode);
    void SetPosition(double x, double y);
    void SetScale(double scaleX, double scaleY);
    void SetScale(double scale);
    void SetVisible(bool visible);
    void SetRotation(double rotation);

    SDL_FRect GetRect();
    bool IsVisible();

    // Attributes

protected:
    // Methods

    // Attributes
    SDL_Texture* texture = nullptr;

    SDL_FRect destRect = { 0, 0, 0, 0 };
    SDL_FRect srcRect = { 0, 0, 0, 0 };
    SDL_Color color { 255, 255, 255, 255 };
    double scaleX = 1.0, scaleY = 1.0;
    double rotation = 0;
    SDL_FlipMode flip = SDL_FLIP_NONE;

    bool is_visible = true;
};

