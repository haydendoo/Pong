#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"
#include "Math.hpp"

class Paddle {
public:
    Paddle(float p_left, float p_right, float p_bot, flaot p_top): left(p_left), right(p_right), bot(p_bot), top(p_top) {}
    void shiftUp();
    void shiftDown();
private:
    float left, right, bot, top;
} paddles[2];

class Ball {
public:
    Ball(Vector2f p_vel, Vector2f p_pos, float p_radius): velocity(p_vel), pos(p_pos), radius(p_radius) {}
    int contact(int left, int right, int bot, int top); // -1 for no contact, 0 1 2 3 for left right bot top
    void bounceHori();
    void bounceVert();
    void updatePos();
    void print() {
        std::cout << "Ball position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    }
private:
    Vector2f velocity, pos;
    float radius;
};