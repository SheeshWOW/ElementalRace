#include "ColliderComponent.h"
#include "../../CollisionManager.h"
#include <vector>

ColliderComponent::ColliderComponent(std::string tag)
{
	this->tag = tag;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Init()
{
	this->transform = &this->entity->GetComponent<TransformComponent>();
}

void ColliderComponent::Update(double delta_time)
{
	if (!this->can_collide) return;

	std::vector<Entity*> entities = Game::entity_manager->GetEntitiesWith<TransformComponent, ColliderComponent>();

	this->is_colliding = false;

	for (Entity*& entity : entities) {
		if (entity == this->entity) continue;

		ColliderComponent& entity_collider_component = entity->GetComponent<ColliderComponent>();
		if (!entity_collider_component.can_collide) continue;

		TransformComponent& entity_transform_component = entity->GetComponent<TransformComponent>();

		SDL_FRect self_collider_rect = this->transform->GetTransformFRect();
		SDL_FRect entity_collider_rect = entity_transform_component.GetTransformFRect();

		bool is_colliding = CollisionManager::CollisionAABB(self_collider_rect, entity_collider_rect);
		
		if (is_colliding) {
			this->last_collided = entity;
			this->is_colliding = is_colliding;

			entity_collider_component.last_collided = this->entity;
			entity_collider_component.is_colliding = is_colliding;

			CollisionManager::ResolveCollision(*this->entity, *entity);
		}
	}
}

void ColliderComponent::Render()
{
}
