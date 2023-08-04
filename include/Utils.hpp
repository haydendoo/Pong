#pragma once

#include <iostream>
#include <random>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define BOUNCE_INCREMENT 1.015f
#define PADDLE_INCREMENT 3

#define WINDOW_W 1280
#define WINDOW_H 720

namespace utils {
    float hireTimeInSeconds();
    float randf(float l, float r);
    int randint(int l, int r);
};