
#ifndef BARWANIENGINE_KEYBOARDCONTROLLER_HPP
#define BARWANIENGINE_KEYBOARDCONTROLLER_HPP

#include "ECS.hpp"
#include "Game.hpp"
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
    void init() override;
    void update() override;
    void eightway();



};

#endif //BARWANIENGINE_KEYBOARDCONTROLLER_HPP
