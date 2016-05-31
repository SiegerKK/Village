//
// Created by sieger on 5/31/16.
//

#ifndef VILLAGE_MAP_H
#define VILLAGE_MAP_H

#include <iostream>

#include "Point.h"

class Map {
public:
    Map(int size, int scale);
    ~Map();

    void init();
    void createHeightMap();
    void makeHeightScale();

    void printHeightToConsole();
    void printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd);
    void printHeightToConsoleScale();
protected:
    int size, scale;
    int **height, **heightScale;
private:
    class Elevation{
    public:
        Elevation(int size, int length);
        void init(Map *map);
        void build(Map *map);
    protected:
    private:
        int size, length;
        Point *points;

    };
};


#endif //VILLAGE_MAP_H
