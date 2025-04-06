#pragma once

#include "../ECS.h"
#include <SDL3/SDL.h>
#include "../../BasicTypes.h"

class TransformComponent : public Component
{
public:
	// Methods
	TransformComponent();
	TransformComponent(float width, float height, float xpos=0, float ypos=0, float rotation=0);

	SDL_FRect GetTransformRect();

	void Translate(float x, float y);
	void Translate(Vector2D vec);

	void SetPosition(float x, float y);
	void SetPosition(Vector2D vec);
	
	void Scale(float x, float y);
	void Scale(Vector2D vec);

	void SetScale(float x, float y);
	void SetScale(Vector2D vec);

	void SetRotation(float rotation);

	// Attributes
	Vector2D position;
	Vector2D scale;

	float rotation = 0;
};

