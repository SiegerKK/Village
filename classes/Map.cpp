//
// Created by sieger on 5/31/16.
//

#include "Map.h"

//----------//----------//----------//
Map::Map(int size, int scale) {
    if(size % scale != 0){
        std::cerr << "ERROR:Map(int size, int scale)\n";
        std::cerr << "--->Wrong scale\n";
        return;
    }

    this->size = size;
    this->scale = scale;

    height = new int*[size];
    for (int i = 0; i < size; ++i) {
        height[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            height[i][j] = 0;
        }
    }

    heightScale = new int*[size / scale];
    for (int i = 0; i < size / scale; ++i) {
        heightScale[i] = new int[size / scale];
        for (int j = 0; j < size / scale; ++j) {
            heightScale[i][j] = 0;
        }
    }
}
Map::~Map() {
    for (int i = 0; i < size; ++i) {
        delete[] height[i];
    }
    delete height;

    for (int i = 0; i < size / scale; ++i) {
        delete[] heightScale[i];
    }
    delete heightScale;
}
//----------//----------//----------//
void Map::init(){
    createHeightMap();

    makeHeightScale();
}
void Map::createHeightMap() {
    //----------//
    Elevation *elevation = new Elevation(500, 5);
    elevation->init(this);
    elevation->build(this);
    delete elevation;
    //----------//

    std::cout << "Map: Made height-map\n";
}
void Map::makeHeightScale(){
    if(size % scale != 0){
        std::cerr << "ERROR:printHeighToConsoleScale(int scale)\n";
        std::cerr << "--->Wrong scale\n";
        return;
    }


    for (int i = 0; i < size / scale - 1; ++i) {
        for (int j = 0; j < size / scale - 1; ++j) {
            double averageValue = 0;
            for (int k = i * scale; k < (i + 1) * scale; ++k) {
                //std::cout << "<---point1--->\n";
                for (int l = j * scale; l < (j + 1) * scale; ++l) {
                    averageValue += height[k][l];
                    //std::cout << k << "-" << l << "\n";
                }
            }
            averageValue /= scale * scale;
            heightScale[i][j] = (int)(averageValue + 0.5);
        }
    }

    std::cout << "Map: Made scaled height-map\n";
}
//----------//----------//----------//
void Map::printHeightToConsole() {
    Map::printHeightToConsole(0, 0, size - 1, size - 1);
}
void Map::printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd) {
    for (int i = yStart; i <= yEnd; ++i) {
        for (int j = xStart; j <= xEnd; ++j) {
            if(height[i][j] < 10)
                std::cout << height[i][j];
            else if((height[i][j] >= 10) && (height[i][j] < 15))
                std::cout << "m";
            else if((height[i][j] >= 15) && (height[i][j] < 20))
                std::cout << "M";
            else
                std::cout << "*";

            std::cout << " ";
        }
        std::cout << "\n";
    }
}
void Map::printHeightToConsoleScale(){
    for (int i = 0; i < size / scale; ++i) {
        for (int j = 0; j < size / scale; ++j) {
            if(heightScale[i][j] < 10)
                std::cout << heightScale[i][j];
            else if((heightScale[i][j] >= 10) && (heightScale[i][j] < 15))
                std::cout << "m";
            else if((heightScale[i][j] >= 15) && (heightScale[i][j] < 20))
                std::cout << "M";
            else
                std::cout << "*";

            std::cout << " ";
        }
        std::cout << "\n";
    }
}

//----------//----------//----------//