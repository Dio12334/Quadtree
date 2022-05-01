#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Point.h"
#include "AABB.h"

class Quadtree{

    public:
        Quadtree(AABB boundary);
        bool insert(Point p);
        void draw(SDL_Renderer* renderer);

    private:
        
        void subdivide();

        static constexpr size_t maxCapacity = 1;
        size_t size;
        
        AABB boundary;
        Quadtree* noreste;
        Quadtree* noroeste;
        Quadtree* sureste;
        Quadtree* suroeste;

        std::vector<Point> points;
};

#endif

