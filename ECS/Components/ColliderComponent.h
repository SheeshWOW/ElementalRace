#pragma once

#include <string>

#include <SDL3/SDL.h>
#include "../ECS.h"
#include "Components.h"
#include "../../Game.h"

class ColliderComponent : public Component
{
public:
	// Methods
	ColliderComponent(std::string tag="Nameless_Collider");
	~ColliderComponent();


	void Init() override;
	void Update(double delta_time) override;
	void Render() override;

	// Attributes
	TransformComponent* transform = nullptr;
	std::string tag;

	bool can_collide = true;
	bool is_colliding = false;
	Entity* last_collided = nullptr;
};

