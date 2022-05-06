#include "Point.h"
#include <SDL2/SDL_render.h>
#include <cmath>

Point::Point(double x, double y): x(x), y(y) {}

void Point::draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int dim = 1;
    SDL_Rect dot{
        static_cast<int>(x - dim),
        static_cast<int>(y - dim),
        3*dim,
        3*dim
    };
    SDL_RenderFillRect(renderer, &dot);
}

int Point::distanceFrom(Point other){
    return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
}
