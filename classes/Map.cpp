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

    heightScale10 = new int*[size / 10];
    for (int i = 0; i < size / 10; ++i) {
        heightScale10[i] = new int[size / 10];
        for (int j = 0; j < size / 10; ++j) {
            heightScale10[i][j] = 0;
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

    for (int i = 0; i < size / 10; ++i) {
        delete[] heightScale10[i];
    }
    delete heightScale10;

    for (int i = 0; i < size / scale; ++i) {
        delete[] heightScale[i];
    }
    delete heightScale;
}
//----------//----------//----------//
void Map::init(){
    createHeightMap();

    makeHeightScale10();
    makeHeightScale();
}
void Map::createHeightMap() {
    //----------//
    Elevation *elevation;
    for (int i = 0; i < (rand() % 10) + 10; ++i) {
        elevation = new Elevation((rand() % 500) + 100, rand() % 10 + 1);
        elevation->init(this, true);
        elevation->build(this);
        delete elevation;

        //----------//
        /*makeHeightScale();
        system("clear");
        printHeightToConsoleScale();*/
        //----------//
    }
    //----------//

    std::cout << "Map: Made height-map\n";
}
void Map::makeHeightScale(){
    if(size % scale != 0){
        std::cerr << "ERROR:makeHeightScale()\n";
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
            heightScale[i][j] = (int)(averageValue + 0.5);
        }
    }

    std::cout << "Map: Made scaled height-map\n";
}
void Map::makeHeightScale10(){
    if(size % 10 != 0){
        std::cerr << "ERROR:makeHeightScale10()\n";
        std::cerr << "--->Wrong scale\n";
        return;
    }


    for (int i = 0; i < size / 10 - 1; ++i) {
        for (int j = 0; j < size / 10 - 1; ++j) {
            double averageValue = 0;
            for (int k = i * 10; k < (i + 1) * 10; ++k) {
                for (int l = j * 10; l < (j + 1) * 10; ++l) {
                    averageValue += height[k][l];
                }
            }
            averageValue /= 10 * 100;
            heightScale10[i][j] = (int)(averageValue + 0.5);
        }
    }

    std::cout << "Map: Made scaled 10 height-map\n";
}
//----------//----------//----------//
void Map::printHeightToConsole() {
    Map::printHeightToConsole(0, 0, size - 1, size - 1);
}
void Map::printHeightToConsole(int x, int y, int r) {
    Map::printHeightToConsole(x - r, y - r, x + r, y + r);
}
void Map::printHeightToConsole(int xStart, int yStart, int xEnd, int yEnd) {
    printHeight(height, xStart, yStart, xEnd, yEnd);
}
void Map::printHeightToConsoleScale(){
    printHeight(heightScale, 0, 0, size / scale - 1, size / scale - 1);
}
//----------//----------//----------//
void Map::printHeight(int **array, int xStart, int yStart, int xEnd, int yEnd) {
    if(xEnd - xStart >= size){
        xStart = 0;
        xEnd = size - 1;
    }
    if(yEnd - yStart >= size){
        yStart = 0;
        yEnd = size - 1;
    }
    if(xStart < 0){
        xEnd -= xStart;
        xStart = 0;
    }
    if(xEnd >= size){
        xStart -= xEnd - (size - 1);
        xEnd -= size - 1;
    }
    if(yStart < 0){
        yEnd -= yStart;
        yStart = 0;
    }
    if(yEnd >= size){
        yStart -= yEnd - (size - 1);
        yEnd -= size - 1;
    }

    //std::cout << xStart << "->" << xEnd << " | " << yStart << "->" << yEnd << "\n";

    for (int i = yStart; i <= yEnd; ++i) {
        for (int j = xStart; j <= xEnd; ++j) {
            if(array[i][j] < 10)
                std::cout << array[i][j];
            else if((array[i][j] >= 10) && (array[i][j] < 15))
                std::cout << "m";
            else if((array[i][j] >= 15) && (array[i][j] < 20))
                std::cout << "M";
            else
                std::cout << "*";

            std::cout << " ";
        }
        std::cout << "\n";
    }

}

//----------//----------//----------//
void Map::writeHeightToPGM(std::string fileName){
    std::ofstream file;
    file.open(fileName.c_str());

    file << "P2\n";
    file << size << " " << size << "\n";
    file << 20 << "\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file << 20 - height[i][j] << " ";
        }
        file << "\n";
    }

    std::cout << "Map: File " << fileName << " was written\n";
    file.close();
}
