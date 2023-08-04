#include "Utils.hpp"
#include <random>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

namespace utils {
    float hireTimeInSeconds() {
        float t = SDL_GetTicks();
        t *= 0.001f;
        return t;
    }

    float randf(float l, float r) {
        return std::uniform_real_distribution<float>(l, r)(rng);
    }

    int randint(int l, int r) {
        return std::uniform_int_distribution<int>(l, r)(rng);
    }
}