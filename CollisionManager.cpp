#include "CollisionManager.h"
#include "ECS/Components/Components.h"

bool CollisionManager::CollisionAABB(const SDL_FRect& rectA, const SDL_FRect& rectB) {
    bool collisionX = (rectA.x + rectA.w >= rectB.x) && (rectB.x + rectB.w >= rectA.x);
    bool collisionY = (rectA.y + rectA.h >= rectB.y) && (rectB.y + rectB.h >= rectA.y);

    return collisionX && collisionY;
}

void CollisionManager::ResolveCollision(Entity& entityA, Entity& entityB)
{
    auto& colliderA = entityA.GetComponent<ColliderComponent>();
    auto& colliderB = entityB.GetComponent<ColliderComponent>();

    SDL_Log("%s colliding with %s!", colliderA.tag.c_str(), colliderB.tag.c_str());
}
