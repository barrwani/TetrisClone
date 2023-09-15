#include "../include/Game.hpp"
#include <iostream>
#include "../include/Utils.hpp"
#include <random>
#include <queue>
#include "../include/Collision.hpp"

//SDL2 ECS Game Engine based on tutorial series by Carl Birch's Tutorial Series
//https://www.youtube.com/watch?v=44tO977slsU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1


//TODO:
// -Fix next piece spawning, issue with setPiece()
// -Tetromino hard drop
// -Fix Collision
// -Tetromino Shapes
// -Rotating
// -Spawning
// -Losing Mechanic
// -Clear needs to be tested for more than one line being cleared at a time

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::justheld = false;
int fallticktime = 1000;
int settime = 300;
int currentpiece = NULL;
Utils::Timer falltimer; //Timer for tetromino falling
Utils::Timer settimer; //Timer for tetromino setting, resets when piece is rotated/moved
Vector2 topleft(588.0f, -66.0f);

int grid[15][10] = {};


//next 5 pieces
std::queue<int> nextfive;

bool inGame = true;
bool Game::isRunning = false;
bool Game::currentpiecegrounded = false;
bool Game::currentpieceonleft = false;
bool Game::currentpieceonright = false;

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
    firstFill();
    spawnTetromino(nextfive.front());
}

void Game::newPiece()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    nextfive.push(std::uniform_int_distribution<int>(1,7)(mt));
}

void Game::firstFill()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < 5; i++)
    {
        nextfive.push(std::uniform_int_distribution<int>(1,7)(mt));
    }
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

void Game::update() {
    manager.refresh();
    manager.update();

    if(Game::currentpiecegrounded)
    {
        setPiece();
        Game::currentpiecegrounded = false;
    }

    if (falltimer.getTicks() > fallticktime) {
        falltimer.stop();
        falltimer.start();
        for (auto &t: tetrominos) {
            if (t->getComponent<TransformComponent>().position.y < 958 && !currentpiecegrounded){
                t->getComponent<TransformComponent>().position.y += 64;
            }
        }
        for (auto &t: tetrominos) {

            for (auto &cc: colliders) {
                SDL_Rect cCol = cc->getCollider();
                if (Collision::AABB(cCol, t->getComponent<CollisionComponent>().collider)) {
                    std::cout << "collider" << std::endl;
                }
            }
        }
    }
}



bool Game::spawnTetromino(int pieceshape)
{
    Game::currentpiecegrounded = false;
    falltimer.start();
    currentpiece = pieceshape;
    //RNG decides the shape, 1-7
    switch (pieceshape){
        case I:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f +(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        case S:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f +(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        case Z:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f+(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        case J:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f +(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        case O:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f +(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        case T:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f +(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        case L:
            for(int y = 1; y <=4; y++)
            {
                auto& block(manager.addEntity());
                block.addComponent<TransformComponent>(973.0f, 62.0f +(64*y), 64, 64, 1);
                block.addComponent<CollisionComponent>("tetromino");
                block.addComponent<SpriteComponent>("tetro");
                block.addComponent<KeyboardController>();
                block.addGroup(groupTetromino);
            }
            return true;
        default:
            return false;

    }

    //The for loop will put the pieces together, and since they'll all have the same keyboard controller the 4 blocks-
    //-should stick together

    //There will be some boundary issues so a relative position of the borders should be kept and used to determine-
    //-things like valid rotations/movement
    //Position is public, process all disallowance of movement in Game script where all 4 pieces are accessible
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
    std::cout << "Line Cleared!" << std::endl;
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
        int col = 0;
        for(int x : y)
        {
            col++;
            if(x == 1)
            {
                cl++;
                //create and place a block at that position
                auto& block(manager.addEntity());
                block.addComponent<CollisionComponent>("block");
                block.addComponent<TransformComponent>(topleft.x + (col * 64), topleft.y + (row * 64)+64, 64, 64, 1);
                block.addComponent<SpriteComponent>("tetro");
                block.addGroup(groupEnvironment);
                colliders.push_back(&block.getComponent<CollisionComponent>());
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


void Game::setPiece()
{
    for(auto& t: tetrominos)
    {
        float xpos = t->getComponent<TransformComponent>().position.x;
        float ypos = t->getComponent<TransformComponent>().position.y;
        int gridx = (xpos - topleft.x)/64 ;
        int gridy = (ypos - topleft.y)/64 -2;
        grid[gridy][gridx] = 1;
        t->delGroup(groupTetromino);
        std::cout << "set" << std::endl;
    }
    tetrominos.clear();
    Game::justheld = false;
    Game::currentpiecegrounded = false;
    Game::currentpieceonright = false;
    Game::currentpieceonleft = false;
    spawnTetromino(nextfive.front());
    nextfive.pop();
    newPiece();
}

void Game::slamPiece()
{
    for(auto& t: tetrominos)
    {
       float xpos = t->getComponent<TransformComponent>().position.x;
       float ypos = t->getComponent<TransformComponent>().position.y;
       int gridx = (xpos - topleft.x)/64;
       int gridy = (ypos - topleft.y)/64;
        for(int y = gridy; y <15 - gridy; y++)
        {
            for(int x = gridx; x < 10-gridx; x++)
            {
                if(grid[y][x] == 1)
                {
                    Game::currentpiecegrounded = true;
                }
                else
                {
                    t->getComponent<TransformComponent>().position.y += 64;
                }
            }
        }
    }
}


void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
bool Game::running() {return isRunning;}

bool Game::holdTetromino() {
    if (currentpiece == NULL)
    {
        currentpiece = nextfive.front();
        justheld = true;
    }
}

void Game::updateTetromino(int x, int y) {
    for(auto& t: tetrominos)
    {
        if(!currentpiecegrounded)
        {
            t->getComponent<TransformComponent>().position.y += y;
        }
        if(!currentpieceonleft && !currentpieceonright)
        {
            if(x > 0)
            {
                t->getComponent<TransformComponent>().position.x += x;
            }
            else if(x < 0)
            {
                t->getComponent<TransformComponent>().position.x += x;
            }
        }

    }
}