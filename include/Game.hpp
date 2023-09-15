#ifndef UNTITLED4_GAME_H
#define UNTITLED4_GAME_H
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include "AssetManager.hpp"

class AssetManager;
class CollisionComponent;

class Game {
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    static void handleEvents();
    static void update();
    static void render();
    void clean();
    static bool spawnTetromino(int pieceshape); //spawns a tetromino
    static void firstFill(); //fills the next 5 pieces array
    static void newPiece(); //spawns a new piece
    bool holdTetromino();
    static void clearLine(int index);
    static bool running();
    static bool currentpiecegrounded; //used to check if the current piece is on the ground
    static bool currentpieceonborder; //used to check if the current piece is on the border
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isRunning;
    static std::vector<CollisionComponent*> colliders; //vector of all colliders
    static AssetManager* assets; //asset manager
    enum groupLabels : std::size_t
    {
        groupTetromino,
        groupColliders,
        groupEnvironment
    };

    //enum for the different tetromino shapes
    enum tetroShapes {
        L = 1,
        S = 2,
        Z = 3,
        J = 4,
        O = 5,
        T = 6,
        I = 7
    };
private:
    int cnt = 0;
    SDL_Window* window{};
};


#endif //UNTITLED4_GAME_H
