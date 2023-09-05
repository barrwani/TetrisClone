#ifndef TETRISCLONE_GAME_H
#define TETRISCLONE_GAME_H
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
    static bool running();

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isRunning;
    static std::vector<CollisionComponent*> colliders;
    static SDL_Rect camera;
    static AssetManager* assets;
    enum groupLabels : std::size_t
    {
        groupPlayers,
        groupColliders,
        groupEnvironment
    };
private:
    int cnt = 0;
    SDL_Window* window{};
};


#endif //TETRISCLONE_GAME_H
