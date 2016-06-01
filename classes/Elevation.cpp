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
    if(log) {
        std::clog << "Elevation.init(...):\n";
        std::clog << "-->center = {" << points[0].x << ", " << points[0].y << "}\n";
    }
    /*points[0].x = 5;
    points[0].y = 5;*/
    for (int i = 1; i < length; ++i) {
        points[i].x = points[i - 1].x + (rand() % (size * 2 + 1) - size);
        points[i].y = points[i - 1].y + (rand() % (size * 2 + 1) - size);
        if(log) {
            std::clog << "-->point  = {" << points[i].x << ", " << points[i].y << "}\n";
        }
    }
}
void Map::Elevation::build(Map *map) {
    for (int k = 0; k < length; ++k) {
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