#pragma once

#include <SDL3/SDL.h>
#include "../ECS.h"
#include "../../BasicTypes.h"

class TransformComponent : public Component
{
public:
	// Methods
	TransformComponent();
	TransformComponent(float width, float height, float xpos=0, float ypos=0, float rotation=0);

	SDL_FRect GetTransformFRect();

	void Translate(float x, float y);
	void Translate(Vector2D vec);

	void SetPosition(float x, float y);
	void SetPosition(Vector2D vec);
	
	void Scale(float x, float y);
	void Scale(Vector2D vec);

	void SetScale(float x, float y);
	void SetScale(Vector2D vec);

	void SetScaleMultiplier(Vector2D vec_multiplier);
	void SetScaleMultiplier(float scale_multiplier);

	void SetRotation(float rotation);

	// Attributes
	Vector2D position;
	Vector2D scale;
	Vector2D scale_multiplier;
	
	Vector2D velocity;

	float rotation = 0;
};

