
#ifndef TETRISCLONE_KEYBOARDCONTROLLER_HPP
#define TETRISCLONE_KEYBOARDCONTROLLER_HPP

#include "ECS.hpp"
#include "Game.hpp"
#include "Utils.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "Vector2.hpp"
#include <iostream>
class SpriteComponent;
class KeyboardController : public Component{

private:
    TransformComponent* transform;
    SpriteComponent* sprite;

    const Uint8* keystates = SDL_GetKeyboardState(nullptr);


public:
    bool onEdge = false;
    bool onGround = false;
    bool otherPieceBlockedleft = false;
    bool otherPieceBlockedright = false;
    void init() override;
    void update() override;
    void eightway();
    void tetris();



};

#endif //TETRISCLONE_KEYBOARDCONTROLLER_HPP
