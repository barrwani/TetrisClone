#include "../include/CollisionComponent.hpp"

void CollisionComponent::init()
{
    if(!entity->hasComponent<TransformComponent>())
    {
        entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    tex = TextureManager::LoadTexture("assets/ColTex.png");
    srcR = {0,0,32,32};
    destR = {collider.x, collider.y, collider.w, collider.h};


}

void CollisionComponent::update()
{
    if(tag != "terrain")
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->getWidth() * transform->getScale();
        collider.h = transform->getHeight() * transform->getScale();
    }
    destR.x = collider.x - Game::camera.x;
    destR.y = collider.y - Game::camera.y;
}

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