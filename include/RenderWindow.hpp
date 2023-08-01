#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
#include "Math.hpp"

class RenderWindow {
public:
    RenderWindow(const char *p_title, int p_w, int p_h);
    inline SDL_Texture* loadTexture(const char *p_filePath);
    inline void cleanUp();
    inline void clear();
    inline void render(Entity &p_entity);
    inline void display();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};