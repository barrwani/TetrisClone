
#ifndef BARWANIENGINE_TILECOMPONENT_HPP
#define BARWANIENGINE_TILECOMPONENT_HPP
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL.h>
#include "Vector2.hpp"
class TileComponent : public Component{

public:
    SDL_Texture * texture;
    SDL_Rect srcRect, destRect;
    Vector2 position;
    TileComponent() = default;


    void update() override;
    void draw() override;
    ~TileComponent() override;




    TileComponent(int srcX, int srcY, int xpos, int ypos, int tsize, int tscale, const std::string& id);


};

#endif //BARWANIENGINE_TILECOMPONENT_HPP
