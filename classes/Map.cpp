//
// Created by sieger on 5/31/16.
//

#include "Map.h"

//----------//----------//----------//
Map::Map(int size, int scale, double relief) {
    time_t seconds = time(0);

    if(size % scale != 0){
        std::cerr << "ERROR:Map(int size, int scale)\n";
        std::cerr << "--->Wrong scale\n";
        return;
    }

    this->size = size;
    this->scale = scale;
    //latitudesAmount = 21;
    this->relief = relief;

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
    bioms = new int*[size];
    for (int i = 0; i < size; ++i) {
        bioms[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            bioms[i][j] = 0;
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

    for (int i = 0; i < size; ++i) {
        delete[] temperature[i];
    }
    delete temperature;

    for (int i = 0; i < size; ++i) {
        delete[] humidity[i];
    }
    delete humidity;

    for (int i = 0; i < size; ++i) {
        delete[] bioms[i];
    }
    delete bioms;
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
    createBiomsMap();
    std::cout << "Map: Bioms map created\n";
    //----------//
    //some another code
    //----------//
    /*makeHeightScale10();
    std::cout << "Map: map scaling 10 created\n";*/
    makeHeightScale();
    std::cout << "Map: map user's scaling created\n";

    std::cout << "Map: Initializing time " << time(0) - seconds << "s\n";
}
void Map::createHeightMap() {
    //----------//
    dimondSquareGeneration();
    //----------//

    std::cout << "Map: Made height-map\n";
}
void Map::createTemperatureMap() {
    int latitudeSize = (int)((size / latitudesAmount) + 0.5);
    for (int i = 0; i < size / 2; ++i) {
        for (int j = 0; j < size; ++j) {
            temperature[i][j] = ((i / latitudeSize) - (latitudesAmount - 1) / 4) - (height[i][j] / 3);
            if(temperature[i][j] > 5)
                temperature[i][j] = 5;
            else if(temperature[i][j] < -5)
                temperature[i][j] = -5;
        }
    }
    for (int i = size / 2; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            temperature[i][j] = ((latitudesAmount - 1) / 4) - ((i - size / 2) / latitudeSize) - (height[i][j] / 3);
            if(temperature[i][j] > 5)
                temperature[i][j] = 5;
            else if(temperature[i][j] < -5)
                temperature[i][j] = -5;
        }
    }

}
void Map::createHumidityMap() {
    for (int i = 0; i < size; ++i) {
        //----------//
        int currentHumidity;
        std::string climateZone = getClimateZone(i);
        if(climateZone == "arctic"){
            currentHumidity = 1;
        } else if(climateZone == "subarctic"){
            currentHumidity = 2;
        } else if(climateZone == "temperate"){
            currentHumidity = 5;
        } else if(climateZone == "tropic"){
            currentHumidity = 2;
        } else if(climateZone == "equatorial"){
            currentHumidity = 9;
        } else {
            currentHumidity = 0;
        }
        //----------//
        for (int j = 0; j < size; ++j) {
            //----------//
            /*if(i != 0)
                humidity[i][j] = ((currentHumidity + humidity[i - 1][j]) / 2) + (rand() % 3 - 1);
            else
                humidity[i][j] = currentHumidity + (rand() % 3 - 1);*/
            humidity[i][j] = currentHumidity/* + (rand() % 3 - 1)*/;
            //----------//
            /*if(height[i][j] > 0) {
                humidity[i][j] -= height[i][j] / 4;
                humidity[i][j] += temperature[i][j] / 2;
            }*/
            //----------//

            if(humidity[i][j] > 10)
                humidity[i][j] = 10;
            else if(humidity[i][j] < 0)
                humidity[i][j] = 0;
        }
    }
}
void Map::createBiomsMap() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if((temperature[i][j] <= -4) && (temperature[i][j] >= -5) && (humidity[i][j] >= 0) && (humidity[i][j] <= 10)){
                //biom - tundra
                bioms[i][j] = 8;
            } else if((temperature[i][j] <= -2) && (temperature[i][j] >= -3) && (humidity[i][j] <= 10) && (humidity[i][j] >= 3)){
                //biom - taiga
                bioms[i][j] = 7;
            } else if((temperature[i][j] <= 1) && (temperature[i][j] >= -3) && (humidity[i][j] <= 2) && (humidity[i][j] >= 0)){
                //biom - plain
                bioms[i][j] = 3;
            } else if((temperature[i][j] <= 2) && (temperature[i][j] >= -1) && (humidity[i][j] <= 6) && (humidity[i][j] >= 3)){
                //biom - forrest
                bioms[i][j] = 1;
            } else if((temperature[i][j] <= 2) && (temperature[i][j] >= -1) && (humidity[i][j] <= 10) && (humidity[i][j] >= 7)){
                //biom - swamp
                bioms[i][j] = 2;
            } else if((temperature[i][j] <= 5) && (temperature[i][j] >= 2) && (humidity[i][j] <= 2) && (humidity[i][j] >= 0)){
                //biom - desert
                bioms[i][j] = 6;
            } else if((temperature[i][j] <= 5) && (temperature[i][j] >= 3) && (humidity[i][j] <= 6) && (humidity[i][j] >= 3)){
                //biom - savanna
                bioms[i][j] = 5;
            } else if((temperature[i][j] <= 5) && (temperature[i][j] >= 3) && (humidity[i][j] <= 10) && (humidity[i][j] >= 7)){
                //biom - jungle
                bioms[i][j] = 4;
            } else {
                bioms[i][j] = -1;
            }
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
    if (xEnd - xStart >= size) {
        xStart = 0;
        xEnd = size - 1;
    }
    if (yEnd - yStart >= size) {
        yStart = 0;
        yEnd = size - 1;
    }
    if (xStart < 0) {
        xEnd -= xStart;
        xStart = 0;
    }
    if (xEnd >= size) {
        xStart -= xEnd - (size - 1);
        xEnd -= size - 1;
    }
    if (yStart < 0) {
        yEnd -= yStart;
        yStart = 0;
    }
    if (yEnd >= size) {
        yStart -= yEnd - (size - 1);
        yEnd -= size - 1;
    }

    //std::cout << xStart << "->" << xEnd << " | " << yStart << "->" << yEnd << "\n";

    for (int i = yStart; i <= yEnd; ++i) {
        for (int j = xStart; j <= xEnd; ++j) {
            if (array[i][j] <= 0)
                std::cout << "~";
            else if (array[i][j] < 10)
                std::cout << array[i][j];
            else if ((array[i][j] >= 10) && (array[i][j] < 15))
                std::cout << "m";
            else if ((array[i][j] >= 15) && (array[i][j] < 20))
                std::cout << "M";
            else
                std::cout << "*";

            std::cout << " ";
        }
        std::cout << "\n";
    }

}

void Map::dimondSquareGeneration() {
    /*height[0][0] = rand() % 21;
    height[0][size - 1] = rand() % 21;
    height[size - 1][0] = rand() % 21;
    height[size - 1][size - 1] = rand() % 21;*/

    height[0][0] = 0;
    height[0][size - 1] = 0;
    height[size - 1][0] = 0;
    height[size - 1][size - 1] = 0;

    int side = size;
    while(side >= 2){
        for (int i = 0; i < size / side - 1; i++) {
            for (int j = 0; j < size / side - 1; j++) {
                dimondSquareGenerationSquare(j * side, i * side, (j + 1) * side, (i + 1) * side);
            }
        }
        /*std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
        int x = 0, y = 0, r = 16;
        std::cout << "side = " << side << " | amount of iter = " << size / side << "\n";
        printHeightToConsole(x, y ,r);
        std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";*/
        for (int i = 0; i < size / (side / 2) - 1; i++) {
            if(i % 2 == 0){
                for (int j = 0; j < size / side - 2; j++) {
                    dimondSquareGenerationDimond(i * (side / 2), side / 2 + j * side, side);
                }
            } else if(i % 2 == 1){
                for (int j = 0; j < size / side - 1; j++) {
                    dimondSquareGenerationDimond(i * (side / 2), j * side, side);
                }
            }
        }

        /*std::cout << "side = " << side << "\n";
        printHeightToConsole(x, y ,r);
        std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";*/

        side /= 2;
    }
}
void Map::dimondSquareGenerationSquare(int x1, int y1, int x2, int y2) {
    int xNew = (x1 + x2) / 2;
    int yNew = (y1 + y2) / 2;
    int dist = x2 - x1;
    height[yNew][xNew] = (height[y1][x1] + height[y1][x2] + height[y2][x1] + height[y2][x2]) / 4 + randomInt(-relief * dist, relief * dist);

    if(height[yNew][xNew] < -30)
        height[yNew][xNew] = -30;
    if(height[yNew][xNew] > 20)
        height[yNew][xNew] = 20;
}
void Map::dimondSquareGenerationDimond(int x, int y, int side) {
    side /= 2;
    if((y - side >= 0))
        height[y][x] += height[y - side][x];
    if((y + side < size))
        height[y][x] += height[y + side][x];
    if((x - side >= 0))
        height[y][x] += height[y][x - side];
    if((x + side < size))
        height[y][x] += height[y][x + side];

    height[y][x] = height[y][x] / 4 + randomInt(-relief * side, relief * side);

    if(height[y][x] < -30)
        height[y][x] = -30;
    if(height[y][x] > 20)
        height[y][x] = 20;

}
int Map::randomInt(int min, int max) {
    int result = rand() % (max - min + 1) + min;
}
std::string Map::getClimateZone(int y) {
    if((y < 0) || (y >= size)) {
        std::cerr << "ERROR: getClimateZone(int x):\n";
        std::cerr << "--> x is not in bounds of map\n";

        return "";
    }
    int currentLatitude = y / ((double)size / latitudesAmount);
    switch (currentLatitude){
        case 0:
        case 1:
            return "arctic";
            break;
        case 2:
        case 3:
            return "subarctic";
            break;
        case 4:
        case 5:
        case 6:
            return "temperate";
            break;
        case 7:
        case 8:
            return "tropic";
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            return "equatorial";
            break;
        case 13:
        case 14:
            return "tropic";
            break;
        case 15:
        case 16:
        case 17:
            return "temperate";
            break;
        case 18:
        case 19:
            return "subarctic";
            break;
        case 20:
        case 21:
            return "arctic";
            break;
        default:
            return "";
            break;
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
            if(height[i][j] > 15)
                file << 5  << " " << 5 << " " << 5 << " ";
            else if(height[i][j] > 10)
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
            if(height[i][j] <= 0)
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
            else if(temperature[i][j] >= -5)
                file << 0 << " " << 15 << " " << 15 << " ";
            else
                file << 20 << " " << 20 << " " << 20 << " ";
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
            //----------//
            /*if(height[i][j] <= 0){
                file << 0 << " " << 0 << " " << 0 << " ";
            } else*/
            //----------//
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
void Map::writeBiomsToPPM(std::string fileName) {
    std::ofstream file;
    file.open(fileName.c_str());

    file << "P3\n";
    file << size << " " << size << "\n";
    file << 20 << "\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            //----------//
            if(height[i][j] <= 0){
                file << 0 << " " << 0 << " " << 15 << " ";
            } else
            //----------//
            switch (bioms[i][j]){
                case 1:
                    //forrest
                    file << 0 << " " << 12 << " " << 0 << " ";
                    break;
                case 2:
                    //swamp
                    file << 0 << " " << 10 << " " << 10 << " ";
                    break;
                case 3:
                    //plain
                    file << 5 << " " << 15 << " " << 0 << " ";
                    break;
                case 4:
                    //jungle
                    file << 0 << " " << 5 << " " << 0 << " ";
                    break;
                case 5:
                    //savanna
                    file << 10 << " " << 15 << " " << 0 << " ";
                    break;
                case 6:
                    //desert
                    file << 15 << " " << 15 << " " << 0 << " ";
                    break;
                case 7:
                    //taiga
                    file << 5 << " " << 10 << " " << 5 << " ";
                    break;
                case 8:
                    //tundra
                    file << 15 << " " << 15 << " " << 15 << " ";
                    break;
                default:
                    file << 20 << " " << 0 << " " << 0 << " ";
                    break;
            }
        }
        file << "\n";
    }

    std::cout << "Map: File " << fileName << " was written\n";
    file.close();
}
