#include "AABB.h"

AABB::AABB(Point center, double halfDimension): center(center), halfDimension(halfDimension){}

bool AABB::containsPoint(Point p){
    return ((p.x >= center.x - halfDimension)&&(p.x <= center.x + halfDimension)&&(p.y >= center.y - halfDimension)&&(p.y <= center.y + halfDimension));
}
