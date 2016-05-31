//
// Created by sieger on 5/31/16.
//

#ifndef VILLAGE_MAP_H
#define VILLAGE_MAP_H

#include <iostream>

class Map {
public:
    Map(int size);
    ~Map();

    void printHeightToConsole();
    void printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd);
    void printHeightToConsoleScale(int scale);
protected:
    int size;
    int **height;
private:
};


#endif //VILLAGE_MAP_H
