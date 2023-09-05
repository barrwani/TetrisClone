#include <SDL.h>
#include <vector>
#include "../include/Game.hpp"


Game* game = nullptr;

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("Tetris", SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED, 800, 640, false);


    while(Game::running())
    {
        frameStart = SDL_GetTicks();
        Game::handleEvents();
        Game::update();
        Game::render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();
    return 0;


}


