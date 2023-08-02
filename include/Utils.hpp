#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define BOUNCE_INCREMENT 1.3f
#define TIME_DECREMENT 0.95f
#define PADDLE_INCREMENT 5

#define WINDOW_W 1280
#define WINDOW_H 720

namespace utils {
    inline float hireTimeInSeconds() {
        float t = SDL_GetTicks();
        t *= 0.001f;
        return t;
    }
};