#ifndef POINT_H
#define POINT_H

#include <SDL2/SDL.h>

struct Point{

    double x;
    double y;

    Point(double x, double y);
    void draw(SDL_Renderer* renderer);

    bool operator == (const Point& p){
        return (p.x == x && p.y == y);
    }
};

#endif
