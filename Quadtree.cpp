#include "Quadtree.h"
#include <SDL2/SDL_render.h>
#include <iostream>

Quadtree::Quadtree(AABB boundary, size_t maxCapacity_): 
    size(0),
    boundary(boundary),
    noreste(nullptr),
    noroeste(nullptr),
    sureste(nullptr),
    suroeste(nullptr)
    {
        maxCapacity = maxCapacity_;
        points.reserve(maxCapacity);
    }

bool Quadtree::insert(Point p){
    if(!boundary.containsPoint(p))
        return false;
    if(points.size() < maxCapacity && !noreste){
        for(auto i = points.cbegin(); i != points.cend(); i++){
            if(i->x == p.x && i->y == p.y)
                return false;
        } 
        points.emplace_back(p);
        return true;
    }
    if(points.size() == maxCapacity){
        for(auto& point : points)
            if(point.x == p.x && point.y == p.y)
                return false;
    }
    if(!noreste)
        subdivide();
    if(noreste->insert(p)) return true;
    if(noroeste->insert(p)) return true;
    if(sureste->insert(p)) return true;
    if(suroeste->insert(p)) return true;
    return false;
}

void Quadtree::subdivide(){

    AABB ne({boundary.center.x + boundary.halfDimension/2, boundary.center.y - boundary.halfDimension/2}, boundary.halfDimension/2);
    AABB no({boundary.center.x - boundary.halfDimension/2, boundary.center.y - boundary.halfDimension/2}, boundary.halfDimension/2);
    AABB se({boundary.center.x + boundary.halfDimension/2, boundary.center.y + boundary.halfDimension/2}, boundary.halfDimension/2);
    AABB so({boundary.center.x - boundary.halfDimension/2, boundary.center.y + boundary.halfDimension/2}, boundary.halfDimension/2);

    noreste = new Quadtree(ne, maxCapacity);
    noroeste = new Quadtree(no, maxCapacity);
    sureste = new Quadtree(se, maxCapacity);
    suroeste = new Quadtree(so, maxCapacity);

    for(auto& point: points){
        if(ne.containsPoint(point))
            noreste->insert(point);
        else if(no.containsPoint(point))
            noroeste->insert(point);
        else if(se.containsPoint(point))
            sureste->insert(point);
        else if(so.containsPoint(point))
            suroeste->insert(point);
    }
    points.clear();
}

void Quadtree::draw(SDL_Renderer* renderer){
    if(!noreste){
        for(auto& point: points)
            point.draw(renderer);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect vertical{
            static_cast<int>(boundary.center.x),
            static_cast<int>(boundary.center.y - boundary.halfDimension),
            1,
            static_cast<int>(2*boundary.halfDimension)
        };
        SDL_RenderFillRect(renderer, &vertical);
        SDL_Rect horizontal{
            static_cast<int>(boundary.center.x - boundary.halfDimension),
            static_cast<int>(boundary.center.y),
            static_cast<int>(2*boundary.halfDimension),
            1
        };
        SDL_RenderFillRect(renderer, &horizontal);
        
        noreste->draw(renderer);
        noroeste->draw(renderer);
        sureste->draw(renderer);
        suroeste->draw(renderer);
    }
}
