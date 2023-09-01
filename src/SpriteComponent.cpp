#include "../include/SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const std::string& id)
{
    setTex(id);
}

SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}



void SpriteComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->getWidth();
    srcRect.h = transform->getHeight();

}


void SpriteComponent::update()
{
    destRect.x = static_cast<int>(transform->position.x - Game::camera.x);
    destRect.y = static_cast<int>(transform->position.y - Game::camera.y);
    destRect.w = transform->getWidth() * transform->getScale();
    destRect.h = transform->getHeight() * transform->getScale();
}

void SpriteComponent::draw()
{
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);

}

void SpriteComponent::setTex(const std::string& id)
{
    texture = Game::assets->GetTexture(id);
}

