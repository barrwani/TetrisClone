#include "../include/KeyboardController.hpp"

void KeyboardController::init()
{
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
}
bool pressed = false;
Uint32 frameStart;
int frameTime;

void KeyboardController::update()
{
    //Instead of using frametime, maybe use Utils timer... it only moves once, but after timer it moves smoothly
    if(frameTime % 20 == 0 && frameTime != 0)
    {
        frameStart = SDL_GetTicks();
        pressed = false;

    }
    tetris();
    if(keystates[SDL_SCANCODE_ESCAPE])
    {
       Game::isRunning = false;
    }

    frameTime = SDL_GetTicks() - frameStart;



}

void KeyboardController::tetris()
{

    if(keystates[SDL_SCANCODE_LEFT] && !pressed)
    {
        pressed = true;
        transform->position.x -=64;
    }
    if(keystates[SDL_SCANCODE_RIGHT] && !pressed)
    {
        pressed = true;
        transform->position.x +=64;
    }
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

