#ifndef BARWANIENGINE_COLLISIONCOMPONENT_HPP
#define BARWANIENGINE_COLLISIONCOMPONENT_HPP
#include <SDL.h>
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include <string>
#include "TextureManager.hpp"

class CollisionComponent :public Component {
private:
    std::string tag;
    TransformComponent* transform;
    SDL_Rect srcR, destR;
    SDL_Texture* tex;


public:
    SDL_Rect collider;

    SDL_Rect getCollider() const {return collider;}
    std::string getTag() const {return tag;}
    TransformComponent* getTransform() const {return transform;}
    CollisionComponent(std::string t);
    CollisionComponent(std::string t, int xpos, int ypos, int size);
    void init() override;
    void update() override;
    void draw() override;


};


#endif //BARWANIENGINE_COLLISIONCOMPONENT_HPP
