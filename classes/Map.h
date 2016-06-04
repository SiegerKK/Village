//
// Created by sieger on 5/31/16.
//

#ifndef VILLAGE_MAP_H
#define VILLAGE_MAP_H

#include <ctime>
#include <fstream>
#include <iostream>

#include "Point.h"

class Map {
public:
    Map(int size, int scale);
    ~Map();

    void init();
    void createHeightMap();
    void makeHeightScale();
    void makeHeightScale10();

    void printHeightToConsole();
    void printHeightToConsole(int x, int y, int r);
    void printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd);
    void printHeightToConsoleScale();

    void writeHeightToPGM(std::string fileName);
protected:
    int size, scale;
    int **height, **heightScale, **heightScale10;
private:
    void printHeight(int **array, int xStart, int yStart, int xEnd, int yEnd);

    class Elevation{
    public:
        Elevation(int size, int length);
        ~Elevation();

        void init(Map *map, bool log);
        void build(Map *map);
    protected:
    private:
        int size, length;
        Point *points;

    };
};


#endif //VILLAGE_MAP_H
