#include "../include/CollisionComponent.hpp"

void CollisionComponent::init()
{
    if(!entity->hasComponent<TransformComponent>())
    {
        entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    //Collision texture
    tex = TextureManager::LoadTexture("assets/coltex.png");

    //Default square for src rect
    srcR = {0,0,32,32};
    //dest rect set to collider rect
    destR = {collider.x, collider.y, collider.w, collider.h};


}

void CollisionComponent::update()
{
    destR = collider;

    //updates collider rect position to match transform position
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->getWidth() * transform->getScale();
    collider.h = transform->getHeight() * transform->getScale();

    //updates relative position to camera
    destR.x = collider.x - Game::camera.x;
    destR.y = collider.y - Game::camera.y;
}

//Initialises Collision Component with collision tag
CollisionComponent::CollisionComponent(std::string t) {tag = t;}


CollisionComponent::CollisionComponent(std::string t, int xpos, int ypos, int size)
{
    tag = t;
    collider.x = xpos;
    collider.y = ypos;
    collider.h = collider.w = size;
}
void CollisionComponent::draw()
{
    TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
}