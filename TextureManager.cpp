#include "TextureManager.h"
#include <SDL3_image/SDL_image.h>

SDL_Texture* TextureManager::LoadTexture(const char* texture_path)
{
    SDL_Texture* texture = IMG_LoadTexture(Game::renderer, texture_path);
    if (texture == nullptr) {
        SDL_Log("IMG_LoadTexture error: %s", SDL_GetError());
        return nullptr;
    }

    return texture;
}
