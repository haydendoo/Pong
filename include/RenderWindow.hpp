#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
#include "Math.hpp"

class RenderWindow {
public:
    RenderWindow(const char *p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char *p_filePath);
    void cleanUp();
    void clear();
    void render(Entity &p_entity);
    void display();
    void drawLine(int x1, int y1, int x2, int y2);
    SDL_Renderer* _renderer();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};