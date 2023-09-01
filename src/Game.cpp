#include "../include/Game.hpp"
#include <iostream>
#include "../include/utils.hpp"
#include "../include/Collision.hpp"

//SDL2 ECS Game Engine based on tutorial series by Carl Birch's Tutorial Series
//https://www.youtube.com/watch?v=44tO977slsU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool renderCollision = true;
bool Game::isRunning = false;

SDL_Rect Game::camera = { 0,0,800,640 };

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());
AssetManager* Game::assets = new AssetManager(&manager);

std::vector<CollisionComponent*> Game::colliders;

Game::Game()
= default;
Game::~Game()
= default;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized!..." << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(window)
            std::cout << "Window created!" << std::endl;
        else
            std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;

    } else
        isRunning = false;

    assets->AddTexture("player", "assets/player.png");

    assets->AddTexture("tile", "assets/dirt.png");


    player.addComponent<TransformComponent>(400.0f, 400.0f, 32 , 32, 2);
    player.addComponent<SpriteComponent>("player");
    player.addComponent<KeyboardController>();
    player.addComponent<CollisionComponent>("player");
    player.addGroup(groupPlayers);


    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300,20,1);
    wall.addComponent<SpriteComponent>("tile");
    wall.addComponent<CollisionComponent>("tile");
    wall.addGroup(groupColliders);
    wall.addGroup(groupEnvironment);
    Game::colliders.emplace_back(&wall.getComponent<CollisionComponent>());



}

auto& players(manager.getGroup(Game::groupPlayers));
auto& environment(manager.getGroup(Game::groupEnvironment));

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update()
{
    SDL_Rect playerCol = player.getComponent<CollisionComponent>().collider;

    manager.refresh();
    manager.update();

    for(auto& cc: colliders)
    {
        SDL_Rect cCol = cc->getCollider();
        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = player.getComponent<TransformComponent>().lastPosition;
        }
    }


    Vector2& position = player.getComponent<TransformComponent>().position;

    camera.x = static_cast<int>(position.x - 400);
    camera.y = static_cast<int>(position.y - 320);

    if (camera.x < 0)
        camera.x = 0;

    if (camera.y < 0)
        camera.y = 0;

    if (camera.x > camera.w)
        camera.x = camera.w;

    if (camera.y > camera.h)
        camera.y = camera.h;
}



void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& e: environment)
    {
        e->draw();
    }
    for(auto& p: players)
    {
        p->draw();
        if(renderCollision)
        {
            p->getComponent<CollisionComponent>().draw();
        }
    }
    if (renderCollision)
    {
        for(auto& c: colliders)
            c->draw();
    }


    SDL_RenderPresent(renderer);

}


void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
bool Game::running() {return isRunning;}


