#include <iostream>
#include <cstdlib>

#include "classes/Map.h"

using namespace std;

int main() {
    srand(time(NULL));

    Map *map = new Map(10000, 1000);
    map->init();

    map->printHeightToConsoleScale();
    map->printHeightToConsole(0, 0, 40, 40);

    delete map;
    return 0;
}