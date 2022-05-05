#ifndef POINT_H
#define POINT_H

#include <SDL2/SDL.h>


struct Point{

    double x;
    double y;

    Point(double x, double y);
    void draw(SDL_Renderer* renderer);

    friend bool operator==(const Point& left, const Point& right) {
        return left.x == right.x && left.y == right.y;
    }
};

#endif
