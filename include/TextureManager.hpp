#ifndef TETRISCLONE_TEXTUREMANAGER_HPP
#define TETRISCLONE_TEXTUREMANAGER_HPP
#include "Game.hpp"

class TextureManager{
    public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};


#endif //TETRISCLONE_TEXTUREMANAGER_HPP
