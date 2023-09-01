#ifndef BARWANIENGINE_SPRITECOMPONENT_HPP
#define BARWANIENGINE_SPRITECOMPONENT_HPP

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

    bool animated = false;
    int frames = 1;
    int speed = 100;
public:
    int animIndex = 0;
    std::map<const char*, Animation> animations;
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    explicit SpriteComponent(const std::string &id);
    SpriteComponent(const std::string& id, bool isAnimated);
    ~SpriteComponent() override;

    void init() override;
    void update() override;
    void draw() override;

    void play(const char* animName);

    void setTex(const std::string& id);
};

#endif //BARWANIENGINE_SPRITECOMPONENT_HPP
