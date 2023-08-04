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

void Paddle::reset() {
    left = s_left;
    right = s_right;
    bot = s_bot;
    top = s_top;
}

float Paddle::getX() {
    return left;
}

float Paddle::getY() {
    return top;
}

int Ball::contact(int p_left, int p_right, int p_bot, int p_top) { // -1 for no contact, 0 1 2 3 for left right bot top
    if(p_top > p_bot) 
        std::cout << "WARNING: Ball::contact() Y COORDINATE IS SUCH THAT TOP < BOTTOM" << std::endl;
            
    if(left > p_right || right < p_left || top > p_bot || bot < p_top) return -1;

    int centre_x = (left+right) / 2, centre_y = (top+bot) / 2;
    if(centre_x <= p_left) return 0;
    if(centre_x >= p_right) return 1;
    if(centre_y >= p_bot) return 2;
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
    left += velocity.x; 
    right += velocity.x;
    top += velocity.y;
    bot += velocity.y;

    if(left <= 0) {
        right -= left;
        left = 0;
    }

    if(top <= 0) {
        bot -= top;
        top = 0;
    }

    if(right >= WINDOW_W) {
        left = WINDOW_W-1 - (right-left);
        right = WINDOW_W-1;
    }

    if(bot >= WINDOW_H) {
        top = WINDOW_H-1 - (bot-top);
        bot = WINDOW_H-1;
    }
}

float Ball::getX() {
    return (left + right) / 2;
}

float Ball::getY() {
    return (top + bot) / 2;
}

void Ball::reset() {
    velocity.x = utils::randf(8.0, 9.0);
    velocity.y = 11.0f / velocity.x;
    if(utils::randint(0,1) == 0) 
        velocity.x = -velocity.x;

    if(utils::randint(0,1) == 0) 
        velocity.y = -velocity.y;

    left = s_left;
    right = s_right;
    bot = s_bot;
    top = s_top;
}