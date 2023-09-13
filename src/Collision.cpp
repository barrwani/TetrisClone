
#include "../include/Collision.hpp"

//checks if two rectangles are colliding
bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB)
{
    if(recA.x + recA.w >= recB.x &&
       recB.x + recB.w >= recA.x &&
       recA.y + recA.h >= recB.y &&
       recB.y + recB.h >= recA.y)
    {
        return true;
    }
    return false;
}


//checks if two collision components are colliding
 bool Collision::AABB(const CollisionComponent& colA, const CollisionComponent& colB)
 {
        if(AABB(colA.getCollider(), colB.getCollider()))
        {
            return true;
        }
        return false;
 }