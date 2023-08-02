#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"
#include "Math.hpp"
#include "Pong.hpp"

void Paddle::shiftUp() {
    if(top - PADDLE_INCREMENT <= 5) { // threshold
        bot -= top-5;
        top = 5;
        return;
    }
    bot -= PADDLE_INCREMENT;
    top -= PADDLE_INCREMENT;
}
void Paddle::shiftDown() {
    if(bot + PADDLE_INCREMENT >= WINDOW_H - 5) {
        top += WINDOW_H - 5 - bot;
        bot = WINDOW_H - 5;
        return;
    }
    bot += PADDLE_INCREMENT;
    top += PADDLE_INCREMENT;
}

int Ball::contact(int left, int right, int bot, int top) { // -1 for no contact, 0 1 2 3 for left right bot top
    if(top < bot) 
        std::cout << "WARNING: Ball::contact() Y COORDINATE IS SUCH THAT TOP < BOTTOM" << std::endl;
            
    float hori = 0;
    if(pos.x < left)
        hori = left - pos.x;
    else if(pos.x > right) 
        hori = pos.x - right;

    float vert = 0; // 2d array format (top < bot)
    if(pos.y < top)
        vert = top - pos.y;
    else if(pos.y > bot) 
        vert = pos.y - bot;

    float dist = hori*hori + vert*vert;
    
    if(dist <= radius*radius) return -1;
    if(pos.x <= left) return 0;
    if(pos.x >= right) return 1;
    if(pos.y >= bot) return 2;
    return 3;
}
void Ball::bounceHori() {
    velocity.x *= -BOUNCE_INCREMENT;
    velocity.y *= BOUNCE_INCREMENT;
}
void Ball::bounceVert() {
    velocity.x *= BOUNCE_INCREMENT;
    velocity.y *= -BOUNCE_INCREMENT;
}
void Ball::updatePos() {
    pos.x += velocity.x;
    pos.y += velocity.y;
    velocity.x *= TIME_DECREMENT;
    velocity.y *= TIME_DECREMENT;
}