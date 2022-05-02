#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Point.h"
#include "AABB.h"

class Quadtree{

    public:
        Quadtree(AABB boundary, size_t = 1);
        bool insert(Point p);
        void draw(SDL_Renderer* renderer);

    private:
        
        void subdivide();

        size_t maxCapacity;
        size_t size;
        
        AABB boundary;
        Quadtree* noreste;
        Quadtree* noroeste;
        Quadtree* sureste;
        Quadtree* suroeste;

        std::vector<Point> points;
};

#endif

