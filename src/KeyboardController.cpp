#include "../include/KeyboardController.hpp"

Utils::Timer timer;
Utils::Timer droptimer;
void KeyboardController::init()
{
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
    Game::currentpiecegrounded = false;
    Game::currentpieceonleft = false;
    Game::currentpieceonright = false;
}
bool pressed = false;
bool fallpressed = false;



void KeyboardController::update()
{
    if(transform->position.y >=958)
    {
        Game::currentpiecegrounded = true;
    }
    if(timer.getTicks() > 100)
    {
        timer.stop();
        pressed = false;

    }
    if(droptimer.getTicks() > 100)
    {
        droptimer.stop();
        fallpressed = false;
    }
    tetris();
    if(keystates[SDL_SCANCODE_ESCAPE])
    {
       Game::isRunning = false;
    }
    if(keystates[SDL_SCANCODE_C])
    {
        if(!Game::justheld)
            Game::holdTetromino();
    }
}

//Tetromino piece movement
void KeyboardController::tetris()
{
    if(keystates[SDL_SCANCODE_LEFT] && !pressed)
    {
        timer.start();
        pressed = true;
        if(transform->position.x > 716 )
        {
            Game::updateTetromino(-64, 0);
            Game::currentpieceonright = false;
        }
        else
            Game::currentpieceonleft = true;
    }
    if(keystates[SDL_SCANCODE_RIGHT] && !pressed)
    {
        timer.start();
        pressed = true;
        if(transform->position.x < 588 + 64 * 10 )
        {
            Game::updateTetromino(64, 0);
            Game::currentpieceonleft = false;
        }
        else
            Game::currentpieceonright = true;
    }
    if(keystates[SDL_SCANCODE_DOWN] && !fallpressed)
    {
        droptimer.start();
        fallpressed = true;

        if(transform->position.y < 958 )
        {
            Game::updateTetromino(0, 64);
            onGround = false;
        }
        else
        {
            Game::currentpiecegrounded = true;
        }
    }
    if(keystates[SDL_SCANCODE_SPACE])
    {
        Game::slamPiece();
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

