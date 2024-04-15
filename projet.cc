// projet.cc par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#include <string>
#include <iostream>
#include <gtkmm/application.h>

#include "gui.h"
#include "simulation.h"

using namespace std;

int main(int argc, char* argv[]) {
    
    if (argc > 2) {
        exit(EXIT_FAILURE);
    }
    string filename = argv[1];

    Simulation simulation;

    simulation.test(filename);
    //simulation.readFile(filename);

    auto app = Gtk::Application::create();

	return app->make_window_and_run<MyEvent>(1, argv);
}
