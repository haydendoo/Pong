#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <unordered_set>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "Pong.hpp"

int main(int argv, char *args[]) {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) 
        std::cout << "SDL_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    if(!(IMG_Init(IMG_INIT_PNG))) 
        std::cout << "IMG_Init HAS FAILED. Error: " << SDL_GetError() << std::endl;

    if(TTF_Init() < 0)
        std::cout << "TTF_Init HAS FAILED. Error: " << TTF_GetError() << std::endl;

    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
        std::cout << "SDL_mixer HAS FAILED. Error: " << Mix_GetError() << std::endl;

    RenderWindow window("Pong", WINDOW_W, WINDOW_H);
    SDL_Event event;

    bool gameRunning = true;

    SDL_Texture *white_square = window.loadTexture("res/gfx/white-square.jpg");
    SDL_Texture *white_paddle = window.loadTexture("res/gfx/white-paddle.jpg");

    Entity ball_entity(Vector2f(WINDOW_W/2 - 16, WINDOW_H/2 - 16), white_square);
    Ball ball_object(Vector2f(0,0), WINDOW_W/2 - 16, WINDOW_W/2 - 16 + ball_entity.getW(), WINDOW_H/2 - 16 + ball_entity.getH(), WINDOW_H/2 - 16);

    ball_object.reset(); // init velocity

    Entity paddle_entity1(Vector2f(16, 232), white_paddle), paddle_entity2(Vector2f(WINDOW_W - 1 - 32 - 16, 232), white_paddle);
    Paddle paddle_object1(16, 16+32-1, 232+256-1, 232), paddle_object2(WINDOW_W - 1 - 32 - 16, WINDOW_W - 1 - 32 - 16 + 32 - 1, 232+256-1, 232);

    const float timeStep = 0.01f;
    float accumulator = 0.0f, currentTime = utils::hireTimeInSeconds();

    int score1 = 0, score2 = 0;

    TTF_Font *font = TTF_OpenFont("res/gfx/arial.ttf", 24);
    SDL_Color color = {255, 255, 255};

    if(!font)
        std::cout << "FAILED TO LOAD FONT. Error: " << TTF_GetError() << std::endl;

    // Congratulations sound effect
    Mix_Chunk* congratsSoundEffect = Mix_LoadWAV("res/gfx/tada-fanfare-a-6313.wav");
    if(congratsSoundEffect == NULL) 
        std::cout << "FAILED TO LOAD SOUND EFFECT. Error: " << Mix_GetError() << std::endl;

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
            
            const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
            if(keyboardState[SDL_SCANCODE_UP])
                paddle_object2.shiftUp();
            if(keyboardState[SDL_SCANCODE_W])
                paddle_object1.shiftUp();
            if(keyboardState[SDL_SCANCODE_DOWN])
                paddle_object2.shiftDown();
            if(keyboardState[SDL_SCANCODE_S])
                paddle_object1.shiftDown();
            if(keyboardState[SDL_SCANCODE_LEFT])
                paddle_object2.shiftDown();
            if(keyboardState[SDL_SCANCODE_A])
                paddle_object1.shiftUp();
            if(keyboardState[SDL_SCANCODE_RIGHT])
                paddle_object2.shiftUp();
            if(keyboardState[SDL_SCANCODE_D])
                paddle_object1.shiftDown();
            
            if(ball_object.getLeft() <= 0) {
                ++score2;
                ball_object.reset();
                paddle_object1.reset();
                paddle_object2.reset();

                // Play audio
                int channel = Mix_PlayChannel(0, congratsSoundEffect, 0);
                if (channel == -1)
                    std::cout << "FAILED TO PLAY SOUND EFFECT. Error: " << Mix_GetError() << std::endl;
            }
            else if(ball_object.getRight() >= WINDOW_W-1) {
                ++score1;
                ball_object.reset();
                paddle_object1.reset();
                paddle_object2.reset();

                // Play audio
                int channel = Mix_PlayChannel(0, congratsSoundEffect, 0);
                if (channel == -1)
                    std::cout << "FAILED TO PLAY SOUND EFFECT. Error: " << Mix_GetError() << std::endl;
            }

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
            
            ball_object.updatePos();
            ball_entity.updatePos( Vector2f(ball_object.getX(), ball_object.getY()) );

            paddle_entity1.updatePos( Vector2f(paddle_object1.getX(), paddle_object1.getY()) );
            paddle_entity2.updatePos( Vector2f(paddle_object2.getX(), paddle_object2.getY()) );

            accumulator -= timeStep;
        }

        window.clear();

        SDL_Surface *text = TTF_RenderText_Solid(font, std::to_string(score1).c_str(), color);
        if(!text) 
            std::cout << "FAILED TO RENDER TEXT. Error: " << TTF_GetError() << std::endl;

        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(window._renderer(), text);
        SDL_Rect src = {0, 0, text->w, text->h}, dst = {200, 150, text->w * 4, text->h * 4};
        SDL_RenderCopy(window._renderer(), text_texture, &src, &dst);

        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text);

        text = TTF_RenderText_Solid(font, std::to_string(score2).c_str(), color);
        if(!text) 
            std::cout << "FAILED TO RENDER TEXT. Error: " << TTF_GetError() << std::endl;

        text_texture = SDL_CreateTextureFromSurface(window._renderer(), text);
        src = {0, 0, text->w, text->h}, dst = {WINDOW_W - 200 - text->w * 4, 150, text->w * 4, text->h * 4};
        SDL_RenderCopy(window._renderer(), text_texture, &src, &dst);

        SDL_DestroyTexture(text_texture);
        SDL_FreeSurface(text);

        window.render(ball_entity);
        window.render(paddle_entity1);
        window.render(paddle_entity2);
        window.drawLine(WINDOW_W/2, 0, WINDOW_W/2, WINDOW_H - 1);

        window.display();
    }

    Mix_FreeChunk(congratsSoundEffect);

    SDL_DestroyTexture(white_square);
    SDL_DestroyTexture(white_paddle);

    TTF_CloseFont(font);

    window.cleanUp();

    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}