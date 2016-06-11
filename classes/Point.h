//
// Created by sieger on 5/31/16.
//

#ifndef VILLAGE_POINT_H
#define VILLAGE_POINT_H

#include <cmath>

class Point {
public:
    int x, y;

    double distance(Point point);
    double distance(double x, double y);
    double angle(Point point);
    double angle(double x, double y);

    static double distance(Point point1, Point point2);
    static double distance(double x1, double y1, double x2, double y2);
    static double angle(Point point1, Point point2);
    static double angle(double x1, double y1, double x2, double y2);
protected:
private:
};


#endif //VILLAGE_POINT_H
