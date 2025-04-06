#include "MovementComponent.h"

MovementComponent::MovementComponent(float move_speed)
{
	this->move_speed = move_speed;
}

void MovementComponent::Init()
{
	this->transform = &this->entity->GetComponent<TransformComponent>();
}

void MovementComponent::Update(double delta_time)
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	Vector2D movement_direction_vec(0, 0);
	ColliderComponent& collider_component = this->entity->GetComponent<ColliderComponent>();

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

	this->transform->Translate(movement_direction_vec * this->move_speed * delta_time);
}

void MovementComponent::Render()
{
}
