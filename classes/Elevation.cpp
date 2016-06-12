//
// Created by sieger on 5/31/16.
//

#include <cstdlib>

#include "Map.h"

Map::Elevation::Elevation(int size, int length) {
    this->size = size;
    this->length = length;
    points = new Point[size];
}
Map::Elevation::~Elevation() {
    delete[] points;
}

void Map::Elevation::init(Map *map, bool log) {
    points[0].x = rand() % map->size;
    points[0].y = rand() % map->size;
    points[1].x = points[0].x + (rand() % (size * 2 + 1) - size);
    points[1].y = points[0].y + (rand() % (size * 2 + 1) - size);
    if(log) {
        std::clog << "Elevation.init(...):\n";
        std::clog << "-->center = {" << points[0].x << ", " << points[0].y << "}\n";
        std::clog << "-->center = {" << points[1].x << ", " << points[1].y << "}\n";
    }
    for (int i = 2; i < length; ++i) {
        points[i] = generatePointInSector(points[i - 2], points[i - 1], size, 60);
        if(log) {
            std::clog << "-->point  = {" << points[i].x << ", " << points[i].y << ", " << Point::angle(points[i - 1], points[i]) << "*}\n";
        }
    }
}
void Map::Elevation::build(Map *map) {
    for (int k = 0; k < length; ++k) {
        int size = rand() % (this->size / 3) + (this->size / 3 * 2);
        for (int i = points[k].y - size; i <= points[k].y + size; ++i) {
            for (int j = points[k].x - size; j <= points[k].x + size; ++j) {
                if((i >= 0) && (i < map->size) && (j >= 0) && (j < map->size)) {
                    if ((points[k].distance(j, i) <= size) && (points[k].distance(j, i) > (size / 2))) {
                        map->height[i][j] += 1;
                    } else if (points[k].distance(j, i) <= (size / 2)) {
                        map->height[i][j] += 2;
                    }
                }
            }
        }
    }
}

Point Map::Elevation::generatePointInSector(Point lastPoint, Point currentPoint, double radius, double angle) {
    double anglePoints = Point::angle(lastPoint, currentPoint);
    //std::clog << "anglePoints:" << anglePoints << "\n";
    double angleNew = (rand() % (int)angle) + anglePoints - (angle / 2);
    if(angleNew > 360)
        angleNew -= 360;
    else if(angleNew < 0)
        angleNew += 360;
    //std::clog << "angleNew:" << angleNew << "\n";

    double radiusNew = rand() % (int)(radius / 2) + (radius / 2);
    Point point;
    point.x = currentPoint.x + (int)(radiusNew * sin(angleNew / 180 * M_PI) + 0.5);
    point.y = currentPoint.y + (int)(radiusNew * cos(angleNew / 180 * M_PI) + 0.5);

    return point;
}
