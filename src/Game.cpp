#include "../include/Game.hpp"
#include <iostream>
#include "../include/Map.hpp"
#include "../include/utils.hpp"
#include "../include/Collision.hpp"

//SDL2 ECS Game Engine based on tutorial series by Carl Birch's Tutorial Series
//https://www.youtube.com/watch?v=44tO977slsU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1

//Once done with tutorial series implement:
//collision layers
//streamline existing code
//make default objects as seperate classes (kinematicbody, staticbody, etc.) instead of initialising ECS components individually
//make game

//current issues:
//what is going on with collision rn bruh


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool renderCollision = true;
bool Game::isRunning = false;

SDL_Rect Game::camera = { 0,0,800,640 };

Map* map;
Manager manager;
auto& player(manager.addEntity());
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

    assets->AddTexture("player", "assets/player_anims.png");
    assets->AddTexture("terrain", "assets/terrain_ss.png");


    map = new Map("terrain", 3, 32);

    map->LoadMap("assets/map.map", 25, 20);



    player.addComponent<TransformComponent>(800.0f, 640.0f, 32 , 32, 2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyboardController>();
    player.addComponent<CollisionComponent>("player");
    player.addGroup(groupPlayers);
    player.addGroup(groupColliders);

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

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
    manager.refresh();
    manager.update();

    for(auto cc: colliders)
    {
        if(Collision::AABB(player.getComponent<CollisionComponent>(), *cc))
        {
            std::cout << "Collision" << std::endl;
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

    for(auto& t: tiles)
        t->draw();



    for(auto& p: players)
    {
        p->draw();
    }
    if (renderCollision)
        for(auto& c: colliders)
            c->draw();

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


