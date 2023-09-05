#ifndef TETRISCLONE_SPRITECOMPONENT_HPP
#define TETRISCLONE_SPRITECOMPONENT_HPP

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "TextureManager.hpp"
#include <SDL.h>
#include "Animation.hpp"
#include <map>



class SpriteComponent : public Component{
private:
    TransformComponent* transform{};
    SDL_Texture* texture{};
    SDL_Rect srcRect{}, destRect{};


public:
    int animIndex = 0;
    std::map<const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    explicit SpriteComponent(const std::string &id);
    ~SpriteComponent() override;

    void init() override;
    void update() override;
    void draw() override;


    void setTex(const std::string& id);
};

#endif //TETRISCLONE_SPRITECOMPONENT_HPP
