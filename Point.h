#ifndef POINT_H
#define POINT_H

#include <SDL2/SDL.h>


struct Point{

    double x;
    double y;

    Point(){}
    Point(double x, double y);
    void draw(SDL_Renderer* renderer);

    int distanceFrom(Point other);
    friend bool operator==(const Point& left, const Point& right) {
        return left.x == right.x && left.y == right.y;
    }
    Point operator + (const Point& right){
        Point result;
        result.x = x + right.x;
        result.y = y + right.y;
        return result;
    }
    Point operator -(const Point& right){
        Point result;
        result.x = x - right.x;
        result.y = y - right.y;
        return result;
    }
};

#endif
