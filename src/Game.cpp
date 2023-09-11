#include "../include/Game.hpp"
#include <iostream>
#include "../include/utils.hpp"
#include <random>
#include "../include/Collision.hpp"

//SDL2 ECS Game Engine based on tutorial series by Carl Birch's Tutorial Series
//https://www.youtube.com/watch?v=44tO977slsU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1


//TODO:
// -Proper Tetromino Movement (left, right, soft drop, hard drop)
// -Tetromino Shapes
// -Setting and Rotating
// -Boundaries and Spawning
// -Next 5 pieces
// -Losing Mechanic
// -Clear needs to be tested for more than one line being cleared at a time


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

int grid[15][10] = {};

bool inGame = true;
bool Game::isRunning = false;


Manager manager;
auto& ui(manager.addEntity());
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
                SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
            std::cout << "Renderer created!" << std::endl;
        }
        isRunning = true;

    } else
        isRunning = false;

    assets ->AddTexture("HUD", "assets/UI.png");
    assets->AddTexture("tetro", "assets/tetromblank.png");


    ui.addComponent<TransformComponent>(0.0f,0.0f, 1080, 1920,1);
    ui.addComponent<SpriteComponent>("HUD");
    ui.addGroup(groupEnvironment);

    spawnTetromino();




}

auto& tetrominos(manager.getGroup(Game::groupTetromino));
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
//    SDL_Rect tetCol = tetromino.getComponent<CollisionComponent>().collider;

    manager.refresh();
    manager.update();

//    for(auto& cc: colliders)
//    {
//        SDL_Rect cCol = cc->getCollider();
//        if (Collision::AABB(cCol, tetCol))
//        {
//            tetromino.getComponent<TransformComponent>().position =
//            tetromino.getComponent<TransformComponent>().lastPosition;
//        }
//    }
//
//
//    Vector2& position = tetromino.getComponent<TransformComponent>().position;
}

bool Game::spawnTetromino()
{
    //For spawning different shapes, have an RNG decide the shape then use switch case and a for loop that runs 4 times

    //The for loop will put the pieces together, and since they'll all have the same keyboard controller the 4 blocks-
    //-should stick together

    //There will be some boundary issues so a relative position of the borders should be kept and used to determine-
    //-things like valid rotations/movement
    //Position is public, process all disallowance of movement in Game script where all 4 pieces are accessible

    auto& tetromino(manager.addEntity());
    tetromino.addComponent<TransformComponent>(973.0f, 62.0f, 64, 64, 1);
    tetromino.addComponent<CollisionComponent>("tetromino");
    tetromino.addComponent<SpriteComponent>("tetro");
    tetromino.addComponent<KeyboardController>();
    tetromino.addGroup(groupTetromino);

}

void Game::clearLine(int index)
{
    //Shifts all lines above cleared line down one space, overwriting the line to be cleared
    for(int y = index; y >=0; y--)
    {
        for(int x = 0; x < 10; x++)
        {
            if(y-1 >=0)
            {
                grid[y][x] = grid[y-1][x];

            }
            //Once the loop reaches the top of the grid it sets the shifted line to 0
            else
                grid[y][x] = 0;
        }
    }

}

void Game::render()
{
    SDL_RenderClear(renderer);
    for (auto& e: environment)
    {
        e->draw();
    }
    for(auto& t: tetrominos)
    {
        t->draw();
    }
    int row = 0;
    for(auto & y : grid)
    {
        row++;
        int cl = 0;
        for(int x : y)
        {
            if(x == 1)
            {
                cl++;
                //render a block at that position
                //add a collisionshape to that position to prevent pieces from going through it
                if(cl == 10)
                {
                    clearLine(row);
                }
            }
        }
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


