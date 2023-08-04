#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Utils.hpp"
#include "Math.hpp"

class Paddle {
public:
    Paddle(float p_left, float p_right, float p_bot, float p_top)
    : left(p_left), right(p_right), bot(p_bot), top(p_top), s_left(p_left), s_right(p_right), s_bot(p_bot), s_top(p_top) {}
    void shiftUp();
    void shiftDown();
    float getX();
    float getY();
    float getLeft() {
        return left;
    }
    float getRight() {
        return right;
    }
    float getBot() {
        return bot;
    }
    float getTop() {
        return top;
    }
    void reset();
private:
    float left, right, bot, top;
    float s_left, s_right, s_bot, s_top;
};

class Ball {
public:
    Ball(Vector2f p_vel, int p_left, int p_right, int p_bot, int p_top)
    : velocity(p_vel), left(p_left), right(p_right), bot(p_bot), top(p_top), s_left(p_left), s_right(p_right), s_bot(p_bot), s_top(p_top) {}
    int contact(int left, int right, int bot, int top); // -1 for no contact, 0 1 2 3 for left right bot top
    void bounceHori();
    void bounceVert();
    void updatePos();
    float getX();
    float getY();
    float getLeft() {
        return left;
    }
    float getRight() {
        return right;
    }
    float getBot() {
        return bot;
    }
    float getTop() {
        return top;
    }
    void reset();
private:
    Vector2f velocity;
    float left, right, bot, top;
    float s_left, s_right, s_bot, s_top;
};