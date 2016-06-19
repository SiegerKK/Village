#include <iostream>
#include <cstdlib>

#include "classes/Map.h"

using namespace std;

int main() {
    srand(time(NULL));
    //srand(1);

    Map *map = new Map(1024 + 1, 41, 0.3);
    map->init();

    //----------//
    map->printHeightToConsoleScale();
    cout << "- - - - - - - - - -\n";
    /*int x = 0, y = 0, r = 20;
    map->printHeightToConsole(x, y ,r);*/
    //----------//
    map->writeHeightToPGM("testHeight.pgm");
    map->writeHeightToPPM("testHeight.ppm");
    map->writeTemperatureToPPM("testTemperature.ppm");
    //map->writeHumidityToPPM("testHumidity.ppm");
    delete map;

    return 0;
}