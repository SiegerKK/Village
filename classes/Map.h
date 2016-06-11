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
        //size - radius of one elevation
        int size;
        //length - count of elevations
        int length;
        //points - array of points, which have coordinates of center of elevation;
        Point *points;

        /**
         *  generatePointInSector(Point lastPoint, Point currentPoint, double radius, double angle)
         *
         *
         *  Make new point in one line with lastPoint and currentPoint(can be changed by angle) in same radius
         *
         *
         *  Variables:
         *
         *  lastPoint, currentPoint - points for calculing angle
         *
         *  radius - distance on which new point will be created
         *
         *  angle - angle of sector on which new point will be created(in degrees)
         */
        Point generatePointInSector(Point lastPoint, Point currentPoint, double radius, double angle);
    };
};


#endif //VILLAGE_MAP_H
