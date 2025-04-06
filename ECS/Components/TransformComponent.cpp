#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	this->position = { 0, 0 };
	this->scale = { 100, 100 };
	this->scale_multiplier = { 1, 1 };
	
	this->velocity = { 0, 0 };

	this->rotation = 0;
}

TransformComponent::TransformComponent(float xscale, float yscale, float xpos, float ypos, float rotation)
{
	this->position = { xpos, ypos };
	this->scale = { xscale, yscale };
	this->scale_multiplier = { 1, 1 };

	this->velocity = { 0, 0 };

	this->rotation = rotation;
}

SDL_FRect TransformComponent::GetTransformFRect()
{
	return {this->position.x, this->position.y, this->scale.x * this->scale_multiplier.x, this->scale.y * this->scale_multiplier.y};
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

void TransformComponent::SetScaleMultiplier(Vector2D vec_multiplier)
{
	this->scale_multiplier = vec_multiplier;
}

void TransformComponent::SetScaleMultiplier(float scale_multiplier)
{
	this->scale_multiplier = { scale_multiplier, scale_multiplier };
}

void TransformComponent::SetRotation(float rotation)
{
	this->rotation = rotation;
}
