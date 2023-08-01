#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
    Entity(Vector2f p_pos, SDL_Texture *p_tex);
    inline Vector2f getPos();
    inline SDL_Texture* getTex();
    inline SDL_Rect getCurrentFrame();
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture *tex;
};