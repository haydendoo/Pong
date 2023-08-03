#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Math.hpp"

class Entity {
public:
    Entity(Vector2f p_pos, SDL_Texture *p_tex);
    Vector2f& getPos();
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    void updatePos(Vector2f p_pos);
    int getW();
    int getH();
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture *tex;
    int w, h;
};