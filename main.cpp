#include <iostream>

#include "classes/Map.h"

using namespace std;

int main() {
    Map *map = new Map(10000);

    //map->printHeightToConsole(0, 0, 20, 20);
    map->printHeightToConsoleScale(1000);
    return 0;
}