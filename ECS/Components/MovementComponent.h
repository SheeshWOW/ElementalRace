#pragma once

#include <SDL3/SDL.h>
#include "../ECS.h"
#include "../../BasicTypes.h"
#include "Components.h"

class MovementComponent : public Component
{
public:
	MovementComponent(float move_speed = 50);
	~MovementComponent() = default;

	void Init() override;
	void Update(double delta_time) override;
	void Render() override;

	TransformComponent* transform = nullptr;
	float move_speed = 0;
};

