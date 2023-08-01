#include <SDL2/SDL.h>
#include <SDL2/SLD_image.h>
#include <iostream>

int main(int agrv, char *args[]) {
    if(SDL_Init(SDL_INIT_VIDEO) > 0) 
        std::cout << "SDL_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    if(!(IMG_Init(IMG_INIT_PNG))) 
        std::cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    std::cout << "Hello World" << std::endl;
    return 0;
}