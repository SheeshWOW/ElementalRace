#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	this->position.x = this->position.y = 0;
	this->scale.x = this->scale.y = 100;
	this->rotation = 0;
}

TransformComponent::TransformComponent(float xscale, float yscale, float xpos, float ypos, float rotation)
{
	this->position.x = xpos;
	this->position.y = ypos;

	this->scale.x = xscale;
	this->scale.y = yscale;

	this->rotation = rotation;
}

SDL_FRect TransformComponent::GetTransformRect()
{
	return {this->position.x, this->position.y, this->scale.x, this->scale.y};
}

void TransformComponent::Translate(float x, float y)
{
	this->position.x += x;
	this->position.y += y;
}

void TransformComponent::Translate(Vector2D vec)
{
	this->position += vec;
}

void TransformComponent::SetPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

void TransformComponent::SetPosition(Vector2D vec)
{
	this->position = vec;
}

void TransformComponent::Scale(float x, float y)
{
	this->scale.x += x;
	this->scale.y += y;
}

void TransformComponent::Scale(Vector2D vec)
{
	this->scale += vec;
}

void TransformComponent::SetScale(float x, float y)
{
	this->scale.x = x;
	this->scale.y = y;
}

void TransformComponent::SetScale(Vector2D vec)
{
	this->scale = vec;
}

void TransformComponent::SetRotation(float rotation)
{
	this->rotation = rotation;
}
