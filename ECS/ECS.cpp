#include "ECS.h"
#include "SDL3/SDL.h"

EntityManager::~EntityManager()
{
}

void EntityManager::Update(double delta_time)
{
    for (auto& e : entities) e->Update(delta_time);
}

void EntityManager::Render()
{
    for (auto& e : entities) e->Render();
}

void EntityManager::Refresh()
{
    entities.erase(
        std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->IsAlive();
            }),
        std::end(entities));
}

Entity& EntityManager::CreateEntity()
{
    Entity* e = new Entity();
    std::unique_ptr<Entity> uPtr{ e };
    entities.emplace_back(std::move(uPtr));
    return *e;
}

void Entity::Update(double delta_time)
{
    for (auto& c : this->components) c->Update(delta_time);
}

void Entity::Render()
{
    for (auto& c : this->components) c->Render();
}

bool Entity::IsAlive() const
{
    return this->is_alive;
}

void Entity::Destroy()
{
    this->is_alive = false;
}