//
// Created by sieger on 5/31/16.
//

#include <cmath>

#include "Point.h"

double Point::distance(Point point) {
    return distance(point.x, point.y);
}
double Point::distance(int x, int y) {
    return pow(((x - this->x) * (x - this->x)) + ((y - this->y) * (y - this->y)), 1.0 / 2.0);
}
