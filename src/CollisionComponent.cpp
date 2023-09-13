#include "../include/CollisionComponent.hpp"

void CollisionComponent::init()
{
    //If entity does not have a transform component, add one
    if(!entity->hasComponent<TransformComponent>())
    {
        entity->addComponent<TransformComponent>();
    }
    //Get the transform component
    transform = &entity->getComponent<TransformComponent>();

    //Collision texture
    tex = TextureManager::LoadTexture("assets/coltex.png");

    //Default square for src rect
    srcR = {0,0,16,16};
    //dest rect set to collider rect
    destR = {collider.x, collider.y, collider.w, collider.h};


}

void CollisionComponent::update()
{
    //updates collider rect position to match transform position
    destR = collider;

    //updates collider rect position to match transform position
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->getWidth() * transform->getScale();
    collider.h = transform->getHeight() * transform->getScale();

    //updates relative position to camera
    destR.x = collider.x ;
    destR.y = collider.y ;
}

//Initialises Collision Component with collision tag
CollisionComponent::CollisionComponent(std::string t) {tag = t;}


CollisionComponent::CollisionComponent(std::string t, int xpos, int ypos, int size)
{
    //Initialises Collision Component with collision tag, position and size
    tag = t;
    collider.x = xpos;
    collider.y = ypos;
    collider.h = collider.w = size;
}
void CollisionComponent::draw()
{
    //Draws collision texture if visibleCollision is toggled
    if(visibleCollision)
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}