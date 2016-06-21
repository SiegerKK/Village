//
// Created by sieger on 5/31/16.
//

#ifndef VILLAGE_MAP_H
#define VILLAGE_MAP_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <queue>

#include "Point.h"

class Map {
public:
    Map(int size, int scale, double relief);
    ~Map();

    void init();
    void createHeightMap();
    void createTemperatureMap();
    void createHumidityMap();

    void makeHeightScale();
    void makeHeightScale10();

    void printHeightToConsole();
    void printHeightToConsole(int x, int y, int r);
    void printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd);
    void printHeightToConsoleScale();

    void writeHeightToPGM(std::string fileName);
    void writeHeightToPPM(std::string fileName);
    void writeTemperatureToPPM(std::string fileName);
    void writeHumidityToPPM(std::string fileName);
protected:
    //int size - size of map(width and height)
    int size;
    //int scale - variable for scaling map;
    int scale;
    //int relief - regulates noise in dimond-square generation
    double relief;
    //int heightMax - max height of terrain
    int heightMax;
    //int height[][] - array with heights all of tiles
    int **height;
    //int heightScale[][] - scaled height[][] with user scaling
    int **heightScale;
    //int heightScale10[][] - scaled height[][] with scaling 10
    int **heightScale10;
    //int tmperature[][] - array with temperatures all of tiles(-5..5)
    int **temperature;
    //int humidity[][] - array with humidity all of tiles(влажность)(0..10)
    int **humidity;
    //int latitudesAmount - amount of latitudes
    const int latitudesAmount = 22;

private:
    void printHeight(int **array, int xStart, int yStart, int xEnd, int yEnd);

    void dimondSquareGeneration();
    void dimondSquareGenerationSquare(int x1, int y1, int x2, int y2);
    void dimondSquareGenerationDimond(int x, int y, int side);

    int randomInt(int min, int max);

    std::string getClimateZone(int y);

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
