#include "../include/KeyboardController.hpp"

void KeyboardController::init()
{
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
}


void KeyboardController::update()
{
    eightway();
}

void KeyboardController::eightway()
{
    transform->direction.x = 0;
    transform->direction.y = 0;

    if (keystates[SDL_SCANCODE_UP])
    {
        if(!keystates[SDL_SCANCODE_DOWN])
        {
            transform->direction.y = -1;
        }

        else
        {
            transform->direction.y = 0;
        }
    }
    if (keystates[SDL_SCANCODE_LEFT])
    {
        if(!keystates[SDL_SCANCODE_RIGHT])
        {
            transform->direction.x = -1;
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        }
        else
        {
            transform->direction.x = 0;
        }
    }
    if (keystates[SDL_SCANCODE_DOWN])
    {
        if(!keystates[SDL_SCANCODE_UP])
        {
            transform->direction.y = 1;
        }
        else
        {
            transform->direction.y = 0;
        }

    }
    if (keystates[SDL_SCANCODE_RIGHT])
    {
        if(!keystates[SDL_SCANCODE_LEFT])
        {
            transform->direction.x = 1;
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
        else
        {
            transform->direction.x = 0;
        }

    }
}

