#include "../include/SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const std::string& id)
{
    setTex(id);
}

SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}


SpriteComponent::SpriteComponent(const std::string& id, bool isAnimated)
{
    animated = isAnimated;

    if(animated)
    {
        Animation idle = Animation(0, 100, 3);
        Animation walk = Animation(1, 100, 8);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        play("Idle");
    }

    setTex(id);

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
    if(animated)
    {
        srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

    }
    srcRect.y = animIndex * transform->getHeight();


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


void SpriteComponent::play(const char* animName)
{
    frames = animations[animName].frames;
    animIndex = animations[animName].index;
    speed = animations[animName].speed;

}

