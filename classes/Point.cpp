//
// Created by sieger on 5/31/16.
//

#include <cmath>

#include "Point.h"

double Point::distance(Point point) {
    return distance(point.x, point.y);
}
double Point::distance(double x, double y) {
    return distance(this->x, this->y, x, y);
}
double Point::angle(Point point) {
    return angle(point.x, point.y);
}
double Point::angle(double x, double y) {
    return angle(this->x, this->y, x, y);
}

//---static---//
double Point::distance(Point point1, Point point2) {
    //return distance(point1.x, point1.y, point2.x, point2.y);
    return point1.distance(point2);
}
double Point::distance(double x1, double y1, double x2, double y2) {
    return pow(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)), 1.0 / 2.0);
}
double Point::angle(Point point1, Point point2) {
    return point1.angle(point2);
}
double Point::angle(double x1, double y1, double x2, double y2) {
    double dy = y2 - y1;
    double d = distance(x1, y1, x2, y2);
    return acos(dy / d)  * (180 / M_PI);
}
