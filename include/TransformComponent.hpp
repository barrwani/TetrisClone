
#ifndef TETRISCLONE_TRANSFORMCOMPONENT_HPP
#define TETRISCLONE_TRANSFORMCOMPONENT_HPP

#include "ECS.hpp"
#include "Vector2.hpp"


class TransformComponent : public Component{
private:
    //Speed multiplier
    int speed = 3;

    int height = 32;
    int width = 32;
    int scale = 1;
public:
    //Position and direction vectors
    Vector2 position;
    Vector2 direction;
    Vector2 lastPosition;
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    int getScale() const {return scale;}

    //Constructors
    TransformComponent();
    TransformComponent(float x, float y);
    TransformComponent(float x, float y, int h, int w, int s);


    //Initialise and update functions
    void init() override;
    void update();


};

#endif //TETRISCLONE_TRANSFORMCOMPONENT_HPP
