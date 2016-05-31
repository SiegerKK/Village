//
// Created by sieger on 5/31/16.
//

#include "Map.h"

//----------//----------//----------//
Map::Map(int size) {
    this->size = size;

    height = new int*[size];
    for (int i = 0; i < size; ++i) {
        height[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            height[i][j] = 0;
        }
    }
}
Map::~Map() {
    for (int i = 0; i < size; ++i) {
        delete[] height[i];
    }
    delete height;
}
//----------//----------//----------//
void Map::printHeightToConsole() {
    Map::printHeightToConsole(0, 0, size - 1, size - 1);
}
void Map::printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd) {
    for (int i = yStart; i <= yEnd; ++i) {
        for (int j = xStart; j < xEnd; ++j) {
            if(height[i][j] < 10)
                std::cout << height[i][j];
            else if((height[i][j] >= 10) && (height[i][j] < 15))
                std::cout << "m";
            else if((height[i][j] >= 15) && (height[i][j] < 20))
                std::cout << "M";
            else
                std::cout << "*";
        }
        std::cout << "\n";
    }
}
void Map::printHeightToConsoleScale(int scale){
    if(size % scale != 0){
        std::cerr << "ERROR:printHeighToConsoleScale(int scale)\n";
        std::cerr << "--->Wrong scale\n";
        return;
    }

    for (int i = 0; i < size / scale; ++i) {
        for (int j = 0; j < size / scale; ++j) {
            double averageValue = 0;
            for (int k = i * scale; k < (i + 1) * scale; ++k) {
                for (int l = j * scale; l < (j + 1) * scale; ++l) {
                    averageValue += height[k][l];
                }
            }
            averageValue /= scale * scale;

            int averageHeight = (int)(averageValue + 0.5);
            if(averageHeight < 10)
                std::cout << averageHeight;
            else if((averageHeight >= 10) && (averageHeight < 15))
                std::cout << "m";
            else if((averageHeight >= 15) && (averageHeight < 20))
                std::cout << "M";
            else
                std::cout << "*";
        }
        std::cout << "\n";
    }
}

//----------//----------//----------//