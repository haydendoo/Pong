#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Pong.hpp"

int main(int argv, char *args[]) {
    if(SDL_Init(SDL_INIT_VIDEO) > 0) 
        std::cout << "SDL_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    if(!(IMG_Init(IMG_INIT_PNG))) 
        std::cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("Pong", WINDOW_W, WINDOW_H);
    SDL_Event event;

    bool gameRunning = true;

    SDL_Texture *white_square = window.loadTexture("res/gfx/white-square.jpg");
    SDL_Texture *white_paddle = window.loadTexture("res/gfx/white-paddle.jpg");

    Entity ball_entity(Vector2f(WINDOW_W/2 - 16, WINDOW_H/2 - 16), white_square);
    Ball ball_object(Vector2f(10,1), WINDOW_W/2 - 16, WINDOW_W/2 - 16 + ball_entity.getW(), WINDOW_H/2 - 16 + ball_entity.getH(), WINDOW_H/2 - 16);

    Entity paddle_entity1(Vector2f(16, 232), white_paddle), paddle_entity2(Vector2f(WINDOW_W - 1 - 32 - 16, 232), white_paddle);
    Paddle paddle_object1(16, 16+32-1, 232+256-1, 232), paddle_object2(WINDOW_W - 1 - 32 - 16, WINDOW_W - 1 - 32 - 16 + 32 - 1, 232+256-1, 232);

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
                switch(event.type) {
                    case SDL_QUIT:
                        gameRunning = false;
                        break;
                    default: 
                        break;
                }
            }
            ball_object.updatePos();
            ball_entity.updatePos( Vector2f(ball_object.getX(), ball_object.getY()) );

            if(ball_object.getTop() <= 0 || ball_object.getBot() >= WINDOW_H - 1) {
                ball_object.bounceVert();
            }

            int temp = ball_object.contact(paddle_object1.getLeft(), paddle_object1.getRight(), paddle_object1.getBot(), paddle_object1.getTop());
            if(temp == 0 || temp == 1) {
                ball_object.bounceHori();
            }
            else if(temp == 2 || temp == 3) {
                ball_object.bounceVert();
            }

            temp = ball_object.contact(paddle_object2.getLeft(), paddle_object2.getRight(), paddle_object2.getBot(), paddle_object2.getTop());
            if(temp == 0 || temp == 1) {
                ball_object.bounceHori();
            }
            else if(temp == 2 || temp == 3) {
                ball_object.bounceVert();
            }

            accumulator -= timeStep;
        }

        window.clear();

        window.render(ball_entity);
        window.render(paddle_entity1);
        window.render(paddle_entity2);

        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}