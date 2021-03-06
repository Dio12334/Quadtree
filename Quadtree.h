#ifndef QUADTREE_H
#define QUADTREE_H

#include <SDL2/SDL.h>
#include <vector>
#include "Point.h"
#include "AABB.h"

class Quadtree{

    public:
        Quadtree(AABB boundary, size_t maxCapacity_ = 1, Quadtree* father = nullptr);
        bool insert(Point p);
        bool remove(Point p);
        void draw(SDL_Renderer* renderer);
        void addPoint(Point p);
        std::vector<Point> queryRange(AABB range);
        Point getClosestPointToCenter(AABB range);

        int getId() const { return id;}
        Quadtree* getfather() const {return father;}
        Quadtree* getnoreste() const {return noreste;}
        Quadtree* getnoroeste() const {return noroeste;}
        Quadtree* getsureste() const {return sureste;}
        Quadtree* getsuroeste() const {return suroeste;}
    private:
        
        void subdivide();
        void join();


        size_t maxCapacity;
        size_t size;
        
        AABB boundary;
        Quadtree* father;
        Quadtree* noreste;
        Quadtree* noroeste;
        Quadtree* sureste;
        Quadtree* suroeste;

        std::vector<Point> points;
        int id;
};

#endif

