#pragma once

#include <SDL3/SDL.h>
#include "ECS/ECS.h"

class CollisionManager
{
public:
	// Methods
	static bool CollisionAABB(const SDL_FRect& rectA, const SDL_FRect& rectB);

	static void ResolveCollision(Entity& entityA, Entity& entityB);
	// Attributes

};

