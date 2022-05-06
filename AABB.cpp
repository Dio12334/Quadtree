#include "AABB.h"
#include <cmath>

AABB::AABB(Point center, double halfDimension): center(center), halfDimension(halfDimension){}

bool AABB::containsPoint(Point p){
    return ((p.x >= center.x - halfDimension)&&(p.x <= center.x + halfDimension)&&(p.y >= center.y - halfDimension)&&(p.y <= center.y + halfDimension));
}

bool AABB::intersects(const AABB& other){
    bool result = false;
    AABB smallestSquare = (other.halfDimension < halfDimension)? other:*this;
    AABB biggestSquare = (other.halfDimension > halfDimension)? other:*this;

    result = result || biggestSquare.containsPoint({smallestSquare.center.x -halfDimension, smallestSquare.center.y - halfDimension});
    result = result || biggestSquare.containsPoint({smallestSquare.center.x +halfDimension, smallestSquare.center.y - halfDimension});
    result = result || biggestSquare.containsPoint({smallestSquare.center.x -halfDimension, smallestSquare.center.y + halfDimension});
    result = result ||biggestSquare.containsPoint({smallestSquare.center.x +halfDimension, smallestSquare.center.y +halfDimension});

    return result;
}
