//
// Created by sieger on 5/31/16.
//

#include "Map.h"

//----------//----------//----------//
Map::Map(int size, int scale) {
    time_t seconds = time(0);

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
    temperature = new int*[size];
    for (int i = 0; i < size; ++i) {
        temperature[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            temperature[i][j] = 0;
        }
    }
    humidity = new int*[size];
    for (int i = 0; i < size; ++i) {
        humidity[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            humidity[i][j] = 0;
        }
    }

    std::cout << "Map: Creating time " << time(0) - seconds << "s\n";
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

    for (int i = 0; i < size / scale; ++i) {
        delete[] temperature[i];
    }
    delete temperature;

    for (int i = 0; i < size / scale; ++i) {
        delete[] humidity[i];
    }
    delete humidity;
}
//----------//----------//----------//
void Map::init() {
    time_t seconds = time(0);
    createHeightMap();
    std::cout << "Map: Height map created\n";
    createTemperatureMap();
    std::cout << "Map: Temperature map created\n";
    createHumidityMap();
    std::cout << "Map: Humidity map created\n";
    //----------//
    //some another code
    //----------//
    makeHeightScale10();
    makeHeightScale();
    std::cout << "Map: Initializing time " << time(0) - seconds << "s\n";
}
void Map::createHeightMap() {
    //----------//
    Elevation *elevation;
    for (int i = 0; i < (rand() % 10) + 10; ++i) {
        elevation = new Elevation((rand() % 100) + 50, rand() % 5 + 5);
        elevation->init(this, true);
        elevation->build(this);
        delete elevation;
    }
    //----------//

    std::cout << "Map: Made height-map\n";
}
void Map::createTemperatureMap() {
    //It divides map on 22 temperature regions(latitudes)
    int latitudesAmount = 2 * 10 + 1;
    int latitudeSize = (int)((size / latitudesAmount) + 0.5);
    for (int i = 0; i < size / 2; ++i) {
        for (int j = 0; j < size; ++j) {
            temperature[i][j] = ((i / latitudeSize) - (latitudesAmount - 1) / 4) - (height[i][j] / 2);
            //----------//
            //It must not depends on height, but watter(ocean, seas, rivers)
            /*if(height[i][j] == 0){
                if(temperature[i][j] > 0)
                    temperature[i][j]--;
                else if(temperature[i][j] < 0)
                    temperature[i][j]++;
            }*/
            //----------//
        }
    }
    for (int i = size / 2; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            temperature[i][j] = ((latitudesAmount - 1) / 4) - ((i - size / 2) / latitudeSize) - (height[i][j] / 2);
            //----------//
            //It must not depends on height, but watter(ocean, seas, rivers)
            /*if(height[i][j] == 0){
                if(temperature[i][j] > 0)
                    temperature[i][j]--;
                else if(temperature[i][j] < 0)
                    temperature[i][j]++;
            }*/
            //----------//
        }
    }
}
void Map::createHumidityMap(){
    int radius = 20;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            //----------//
            /*double humidityCoef = 0.0;
            int amount = 0, amountWatter = 0;
            for (int k = i - radius; k < i + radius; ++k) {
                for (int l = j - radius; l < j + radius; ++l) {
                    if((k >= 0) && (k < size) && (l >= 0) && (l < size)){
                        //----------//
                        //It must not depends on height, but watter(ocean, seas, rivers)
                        if(height[k][l] == 0){
                            amountWatter++;
                        }
                        //----------//
                        amount++;
                    }
                }
            }
            humidityCoef = ((double)amountWatter) / ((double)amount) * 10;
            humidity[i][j] = (int)(humidityCoef + 0.49) - (height[i][j] / 4);
            if(humidity[i][j] < 0)
                humidity[i][j] = 0;*/
            //----------//
        }
    }
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
            if(height[i][j] >= 20)
                file << 0 << " ";
            else if(height[i][j] <= 0)
                file << 20 << " ";
            else
                file << 20 - height[i][j] << " ";
        }
        file << "\n";
    }

    std::cout << "Map: File " << fileName << " was written\n";
    file.close();
}

void Map::writeHeightToPPM(std::string fileName){
    std::ofstream file;
    file.open(fileName.c_str());

    file << "P3\n";
    file << size << " " << size << "\n";
    file << 20 << "\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(height[i][j] > 10)
                file << 5  << " " << 5 << " " << 5 << " ";
            else if(height[i][j] > 7)
                file << 10  << " " << 10 << " " << 10 << " ";
            else if(height[i][j] > 0)
                file << 20 << " " << 20 << " " << 20 << " ";
            else if(height[i][j] <= 0)
                file << 0 << " " << 0 << " " << 15 << " ";
            /*else
                file << 20 - height[i][j] << " " << 20 - height[i][j] << " " << 20 - height[i][j] << " ";*/
        }
        file << "\n";
    }

    std::cout << "Map: File " << fileName << " was written\n";
    file.close();
}
void Map::writeTemperatureToPPM(std::string fileName) {
    std::ofstream file;
    file.open(fileName.c_str());

    file << "P3\n";
    file << size << " " << size << "\n";
    file << 20 << "\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            //----------//
            if(height[i][j] == 0)
                file << 0  << " " << 0 << " " << 0 << " ";
            else
            //----------//
            if(temperature[i][j] >= 4)
                file << 15  << " " << 0 << " " << 0 << " ";
            else if(temperature[i][j] >= 2)
                file << 15  << " " << 15 << " " << 0 << " ";
            else if(temperature[i][j] >= -1)
                file << 0 << " " << 15 << " " << 0 << " ";
            else if(temperature[i][j] >= -3)
                file << 0 << " " << 0 << " " << 15 << " ";
            else
                file << 0 << " " << 15 << " " << 15 << " ";
        }
        file << "\n";
    }

    std::cout << "Map: File " << fileName << " was written\n";
    file.close();
}
void Map::writeHumidityToPPM(std::string fileName) {
    std::ofstream file;
    file.open(fileName.c_str());

    file << "P3\n";
    file << size << " " << size << "\n";
    file << 20 << "\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            //std::cout << humidity[i][j] << "\n";
            switch (humidity[i][j]){
                case 10:
                    file << 0 << " " << 0 << " " << 20 << " ";
                    break;
                case 9:
                    file << 2 << " " << 0 << " " << 18 << " ";
                    break;
                case 8:
                    file << 4 << " " << 0 << " " << 16 << " ";
                    break;
                case 7:
                    file << 6 << " " << 0 << " " << 14 << " ";
                    break;
                case 6:
                    file << 8 << " " << 0 << " " << 12 << " ";
                    break;
                case 5:
                    file << 10 << " " << 0 << " " << 10 << " ";
                    break;
                case 4:
                    file << 12 << " " << 0 << " " << 8 << " ";
                    break;
                case 3:
                    file << 14 << " " << 0 << " " << 6 << " ";
                    break;
                case 2:
                    file << 16 << " " << 0 << " " << 4 << " ";
                    break;
                case 1:
                    file << 18 << " " << 0 << " " << 2 << " ";
                    break;
                case 0:
                    file << 20 << " " << 0 << " " << 0 << " ";
                    break;
            }
        }
        file << "\n";
    }

    std::cout << "Map: File " << fileName << " was written\n";
    file.close();
}
