#ifndef AABB_H
#define AABB_H

#include "Point.h"

struct AABB{
    Point center;
    double halfDimension;
    AABB(Point center, double halfDimension);
    bool containsPoint(Point p);
};

#endif

