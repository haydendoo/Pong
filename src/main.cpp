#include <SDL2/SDL.h>
#include <SDL2/SLD_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

int main(int agrv, char *args[]) {
    if(SDL_Init(SDL_INIT_VIDEO) > 0) 
        std::cout << "SDL_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    if(!(IMG_Init(IMG_INIT_PNG))) 
        std::cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Pong", 1280, 720);
    SDL_Event event;

    bool gameRunning = true;

    SDL_Texture *grass_texture = window.loadTexture("res/gfx/grass.png");
    Entity entities[3] = { Entity(Vector2f(0,0), grass_texture),
                           Entity(Vector2f(0,30), grass_texture),
                           Entity(Vector2f(30,30), grass_texture) };

    const float timeStep = 0.01f;
    float accumulator = 0.0f, currentTime = utils::hireTimeInSeconds();

    while(gameRunning) {

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        if(frameTime > 0.25f) 
            frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= timeStep) {
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT)
                    gameRunning = false;
            }
            accumulator -= timeStep;
        }

        window.clear();

        for(int i = 0; i < 3; ++i) {
            window.render(entities[i]);
        }

        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}