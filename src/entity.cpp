#include "Entity.hpp"
#include "Math.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture *p_tex)
: pos(p_pos), tex(p_tex) {
    currentFrame.x = 0;
    currentFrame.y = 0;
    SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
} 

Vector2f& Entity::getPos() {
    return pos;
}

SDL_Texture* Entity::getTex() {
    return tex;
}

SDL_Rect Entity::getCurrentFrame() {
    return currentFrame;
}
