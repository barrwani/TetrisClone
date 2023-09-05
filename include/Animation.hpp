
#ifndef BARWANIENGINE_ANIMATION_HPP
#define BARWANIENGINE_ANIMATION_HPP


struct Animation{

    int index;
    int speed;
    int frames;

    Animation() {}
    Animation(int i, int s, int f) {index = i; speed = s; frames = f; }
};


#endif //BARWANIENGINE_ANIMATION_HPP
