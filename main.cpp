#include <iostream>
#include <cstdlib>

#include "classes/Map.h"

using namespace std;

int main() {
    srand(time(NULL));

    Map *map = new Map(10000, 1000);
    map->init();

    map->printHeightToConsoleScale();
    cout << "- - - - - - - - - -\n";
    //----------//
    int x = 0, y = 0, r = 50;
    map->printHeightToConsole(x, y ,r);
    //map->printHeightToConsole(0, 0, 40, 40);
    //----------//

    map->writeHeightToPGM("test.pgm");
    delete map;
    return 0;
}