#include "Quadtree.h"
#include <SDL2/SDL_render.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

Quadtree::Quadtree(AABB boundary, size_t maxCapacity_, Quadtree* father): 
    maxCapacity(maxCapacity_),
    size(0),
    boundary(boundary),
    father(father),
    noreste(nullptr),
    noroeste(nullptr),
    sureste(nullptr),
    suroeste(nullptr)
    {
        static int idsetter = 0;
        id = ++idsetter;
        points.reserve(maxCapacity);
    }

bool Quadtree::insert(Point p){
    if(!boundary.containsPoint(p))
        return false;
    if(points.size() < maxCapacity && !noreste){
        //chequeamos que el punto no a sido insertado antes
        if(std::find(points.cbegin(), points.cend(), p) != points.cend())      
            return false;
        //en caso no haya sido insertado, insertamos
        points.emplace_back(p);
        ++size;
        return true;
    }
    if(points.size() == maxCapacity){
        //Chequeamos que el punto no a sido insertado antes
        if(std::find(points.cbegin(), points.cend(), p) != points.cend())       
            return false;
    }
    if(!noreste)
        // si el area ya esta llena de puntos particionamos esa area
        subdivide();
    // insertamos el punto en el area que corresponde
    if(noreste->insert(p) || noroeste->insert(p) || sureste->insert(p) || suroeste->insert(p)){
        ++size;
        return true;
    }
    return false;
}

bool Quadtree::remove(Point p){
    if(!boundary.containsPoint(p))
        return false;
    if(points.size() <= maxCapacity && !noreste){
        // buscamos el punto y lo eliminamos
        auto it = std::find(points.begin(), points.end(), p);
        if(it != points.end()){
            points.erase(it);
            --size;
            return true;
        }
        return false;
    }
    else if(noreste){
        // chequeamos sus particiones
        if(noreste->remove(p) || noroeste->remove(p) || sureste->remove(p) || suroeste->remove(p)){
            --size;
            if(size <= maxCapacity)
                join();
            return true;
        }
    }
    return false;
}

void Quadtree::subdivide(){
    double centerX = boundary.center.x, centerY = boundary.center.y;
    double halfDimension = boundary.halfDimension;

    // creamos las 4 sub areas
    AABB ne({centerX + halfDimension/2, centerY - halfDimension/2}, halfDimension/2);
    AABB no({centerX - halfDimension/2, centerY - halfDimension/2}, halfDimension/2);
    AABB se({centerX + halfDimension/2, centerY + halfDimension/2}, halfDimension/2);
    AABB so({centerX - halfDimension/2, centerY + halfDimension/2}, halfDimension/2);
    
    // las agregamos al quadtree
    noreste = new Quadtree(ne, maxCapacity, this);
    noroeste = new Quadtree(no, maxCapacity, this);
    sureste = new Quadtree(se, maxCapacity, this);
    suroeste = new Quadtree(so, maxCapacity, this);

    // pasamos los puntos a las respectivas sub areas
    for(auto& point: points){
        if(ne.containsPoint(point))
            noreste->addPoint(point);
        else if(no.containsPoint(point))
            noroeste->addPoint(point);
        else if(se.containsPoint(point))
            sureste->addPoint(point);
        else if(so.containsPoint(point))
            suroeste->addPoint(point);
    }

    //limpiamos el nodo interno de los puntos que teniamos
    points.clear();
}

void Quadtree::join(){
    // si tenemos sub areas
    if(noreste){
        //llamamos a las sub areas para que se junten
        noreste->join();
        noroeste->join();
        sureste->join();
        suroeste->join();
        
        // liberamos la memoria
        delete noreste;
        delete noroeste;
        delete sureste;
        delete suroeste;

        noreste = noroeste = suroeste = sureste = nullptr;
    }
    else{
        // si no tenemos sub areas tenemos puntos, estos los mandamos al padre
        for(auto& point: points)
            father->points.emplace_back(point);
        points.clear();
        father = nullptr;
    }
}

void Quadtree::draw(SDL_Renderer* renderer){
    // si no tnemos sub areas tenemos puntos los cuales dibujamos
    if(!noreste){
        for(auto& point: points)
            point.draw(renderer);
    }
    else{
        // sino dibujamos las divisiones 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect vertical{
            static_cast<int>(boundary.center.x),
            static_cast<int>(boundary.center.y - boundary.halfDimension),
            1,
            static_cast<int>(std::ceil(2*boundary.halfDimension))
        };
        SDL_RenderFillRect(renderer, &vertical);
        SDL_Rect horizontal{
            static_cast<int>(boundary.center.x - boundary.halfDimension),
            static_cast<int>(boundary.center.y),
            static_cast<int>(std::ceil(2*boundary.halfDimension)),
            1
        };
        SDL_RenderFillRect(renderer, &horizontal);
        
        // luego dibujamos las sub areas
        noreste->draw(renderer);
        noroeste->draw(renderer);
        sureste->draw(renderer);
        suroeste->draw(renderer);
    }
}

void Quadtree::addPoint(Point p){
    points.emplace_back(p);
    ++size;
}

std::vector<Point> Quadtree::queryRange(AABB range){
    std::vector<Point> pointsInRange;
    if(!boundary.intersects(range))
        return pointsInRange;
    for(auto& point: points)
        if(range.containsPoint(point))
            pointsInRange.emplace_back(point);
    if(!noreste)
        return pointsInRange;

    std::vector<Point> ne = noreste->queryRange(range);
    pointsInRange.insert(pointsInRange.end(), ne.begin(), ne.end());
    std::vector<Point> no = noroeste->queryRange(range);
    pointsInRange.insert(pointsInRange.end(), no.begin(), no.end());
    std::vector<Point> se = sureste->queryRange(range);
    pointsInRange.insert(pointsInRange.end(), se.begin(), se.end());
    std::vector<Point> so = suroeste->queryRange(range);
    pointsInRange.insert(pointsInRange.end(), so.begin(), so.end());

    return pointsInRange;
}

Point Quadtree::getClosestPointToCenter(AABB range){
    std::vector<Point> pointsInRange = queryRange(range);
    Point closest(100000, 100000);
    for(auto& point: pointsInRange){
        if(point.distanceFrom(range.center) < closest.distanceFrom(range.center))
            closest = point;
    }
    return closest;
}
