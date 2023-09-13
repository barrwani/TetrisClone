#include "../include/KeyboardController.hpp"

Utils::Timer timer;

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
    if(timer.getTicks() > 100)
    {
        timer.stop();
        pressed = false;

    }
    tetris();
    if(keystates[SDL_SCANCODE_ESCAPE])
    {
       Game::isRunning = false;
    }





}

//Tetromino piece movement
void KeyboardController::tetris()
{
    if(keystates[SDL_SCANCODE_LEFT] && !pressed)
    {
        timer.start();
        pressed = true;
        transform->position.x -=64;
    }
    if(keystates[SDL_SCANCODE_RIGHT] && !pressed)
    {
        timer.start();
        pressed = true;
        transform->position.x +=64;
    }
}

//8 way movement, not used in this game
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

