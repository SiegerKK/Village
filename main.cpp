#include <iostream>
#include <cstdlib>

#include "classes/Map.h"

using namespace std;

int main() {
    srand(time(NULL));

    Map *map = new Map(1000, 100);
    map->init();

    //----------//
    map->printHeightToConsoleScale();
    cout << "- - - - - - - - - -\n";
    int x = 0, y = 0, r = 20;
    map->printHeightToConsole(x, y ,r);
    //----------//
    map->writeHeightToPGM("test.pgm");
    delete map;

    return 0;
}