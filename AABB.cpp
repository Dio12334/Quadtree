#include "AABB.h"
#include <cmath>

AABB::AABB(Point center, double halfDimension): center(center), halfDimension(halfDimension){}

bool AABB::containsPoint(Point p){
    return ((p.x >= center.x - halfDimension)&&(p.x <= center.x + halfDimension)&&(p.y >= center.y - halfDimension)&&(p.y <= center.y + halfDimension));
}

bool AABB::intersects(const AABB& other){
    return (center.distanceFrom(other.center) < (2*halfDimension + 2*other.halfDimension) || center.distanceFrom(other.center) < (std::sqrt(2*std::pow(halfDimension,2)) + std::sqrt(2*std::pow(other.halfDimension, 2))));
}
