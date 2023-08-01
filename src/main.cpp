#include <SDL2/SDL.h>
#include <SDL2/SLD_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

int main(int agrv, char *args[]) {
    if(SDL_Init(SDL_INIT_VIDEO) > 0) 
        std::cout << "SDL_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    if(!(IMG_Init(IMG_INIT_PNG))) 
        std::cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Pong", 1280, 720);
    SDL_Event event;

    bool gameRunning = true;

    while(gameRunning) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                gameRunning = false;
            }
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}