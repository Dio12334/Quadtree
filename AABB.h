#ifndef AABB_H
#define AABB_H

#include "Point.h"

// Axis-aligned bounding box with half dimension and center
struct AABB{

    Point center;
    double halfDimension;

    AABB(Point center, double halfDimension);
    bool containsPoint(Point p);
};

#endif

