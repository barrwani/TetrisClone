#ifndef UNTITLED4_UTILS_H
#define UNTITLED4_UTILS_H
#include <SDL.h>


namespace Utils
{
    class Timer
    {
    public:
        Timer()
        {
            startTicks = 0;
            pausedTicks = 0;
            paused = false;
            started = false;
        }
        ~Timer()
        {
            stop();
        }
        void start()
        {
            started = true;
            paused = false;
            startTicks = SDL_GetTicks();
            pausedTicks = 0;
        }
        void stop()
        {
            started = false;
            paused = false;
            startTicks = 0;
            pausedTicks = 0;
        }
        void pause()
        {
            if (started && !paused)
            {
                paused = true;
                pausedTicks = SDL_GetTicks() - startTicks;
                startTicks = 0;
            }
        }
        void unpause()
        {
            if (started && paused)
            {
                paused = false;
                startTicks = SDL_GetTicks() - pausedTicks;
                pausedTicks = 0;
            }
        }
        Uint32 getTicks() const
        {
            Uint32 time = 0;
            if (started)
            {
                if (paused)
                {
                    time = pausedTicks;
                }
                else
                {
                    time = SDL_GetTicks() - startTicks;
                }
            }
            return time;
        }
        bool isStarted() const{ return started; }
        bool isPaused() const{ return paused && started; }

    private:
        Uint32 startTicks;
        Uint32 pausedTicks;
        bool paused;
        bool started;
    };

    inline float hireTimeInSeconds()
    {
        float t = SDL_GetTicks();
        t *=0.001f;
        return t;
    }

}


#endif //UNTITLED4_UTILS_H
