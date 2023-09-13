#include "../include/SpriteComponent.hpp"


//constructor
SpriteComponent::SpriteComponent(const std::string& id)
{
    setTex(id);
}

//destructor
SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}


//initializes the sprite
void SpriteComponent::init()
{
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->getWidth();
    srcRect.h = transform->getHeight();

}


//updates the position of the sprite
void SpriteComponent::update()
{
    destRect.x = static_cast<int>(transform->position.x );
    destRect.y = static_cast<int>(transform->position.y);
    destRect.w = transform->getWidth() * transform->getScale();
    destRect.h = transform->getHeight() * transform->getScale();
}

//draws the sprite
void SpriteComponent::draw()
{
    TextureManager::Draw(texture, srcRect, destRect, spriteFlip);

}

//sets the texture of the sprite
void SpriteComponent::setTex(const std::string& id)
{
    texture = Game::assets->GetTexture(id);
}

