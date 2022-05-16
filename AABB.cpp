#include "AABB.h"
#include <cmath>

AABB::AABB(Point center, double halfDimension): center(center), halfDimension(halfDimension){}

AABB::AABB(Point center, double totalX, double totalY): center(center), dividingPoint(0, 0), totalX(totalX), totalY(totalY), halfDimension(0){
    
}

bool AABB::containsPoint(Point p){
    return ((p.x >= center.x - totalX/2)&&(p.x <= center.x + totalX/2)&&(p.y >= center.y - totalY/2)&&(p.y <= center.y + totalY/2));
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
