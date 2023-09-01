#include "SDL.h"
#include "CollisionComponent.hpp"
#ifndef BARWANIENGINE_COLLISION_HPP
#define BARWANIENGINE_COLLISION_HPP


class Collision {
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const CollisionComponent& colA, const CollisionComponent& colB);

};


#endif //BARWANIENGINE_COLLISION_HPP
