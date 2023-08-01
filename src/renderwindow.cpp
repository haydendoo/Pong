#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char *p_title, int p_w, int p_h)
: window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    
    if(window == NULL) 
        std::cout << "FAILED TO CREATE WINDOW. Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

inline SDL_Texture* loadTexture(const char *p_filePath) {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    
    if(texture == NULL) 
        std::cout << "FAILED TO LOAD TEXTURE. Error: " << SDL_GetError() << std::endl;

    return texture;
}

inline void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

inline void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

inline void RenderWindow::render(SDL_Texture *p_tex) {
    SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

inline void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}