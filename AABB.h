#ifndef AABB_H
#define AABB_H

#include "Point.h"
#include <iostream>
// Axis-aligned bounding box with half dimension and center
struct AABB{

    Point center;
    Point dividingPoint;
    double totalX, totalY;
    double halfDimension;

    AABB(Point center, double halfDimension);
    AABB(Point center, double totalX, double totalY);
    bool containsPoint(Point p);
    bool intersects(const AABB& other);
    void print(){
        std::cout<<"center: "<<center.x<<" "<<center.y<<" div:"<<dividingPoint.x<<" "<<dividingPoint.y<<"lenghts: "<<totalX<<" "<<totalY<<"\n";
    }
};

#endif

