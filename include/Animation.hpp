
#ifndef TETRISCLONE_ANIMATION_HPP
#define TETRISCLONE_ANIMATION_HPP


struct Animation{

    int index;
    int speed;
    int frames;

    Animation() {}
    Animation(int i, int s, int f) {index = i; speed = s; frames = f; }
};


#endif //TETRISCLONE_ANIMATION_HPP
