// projet.cc par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#include <string>
#include <iostream>

#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc > 2) {
        return 1;
    }
    string filename = argv[1];

    Simulation simulation;

    simulation.readFile(filename);

    return 0;
}
