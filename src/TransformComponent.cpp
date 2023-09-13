#include "../include/TransformComponent.hpp"

//Basic Directions
Vector2 LEFT = Vector2(-1.0f, 0.0f);
Vector2 RIGHT = Vector2(1.0f, 0.0f);
Vector2 UP = Vector2(0.0f, -1.0f);
Vector2 DOWN = Vector2(0.0f, 1.0f);
Vector2 ZERO = Vector2(0.0f, 0.0f);





TransformComponent::TransformComponent()
{
    //initial position top-left
    position = ZERO;
}

TransformComponent::TransformComponent(float x, float y)
{
    //Set the initial position
    position.x = x;
    position.y = y;
}

TransformComponent::TransformComponent(float x, float y, int h, int w, int s)
{
    //Set the initial position, height, width and scale
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = s;
}


void TransformComponent::init()
{
    //Initialise with no direction
    direction = ZERO;
}

void TransformComponent::update()
{
    //Normalise the direction vector, same speed all directions
    direction.Normalise();

    lastPosition = position;

    //Move the entity
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}