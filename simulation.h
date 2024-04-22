// simulation.h par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <random>
#include "shape.h"
#include "lifeform.h"


class Simulation{
private:
    std::string filename;
    std::vector<Corail> coraux;
    std::vector<Algue> algues;
    std::vector<Scavenger> scavengers;
    bool sim_success = true; 
    std::default_random_engine generator;

public:
    bool naissance_alg = false;
    std::vector<std::vector<double>> storeTokens(std::ifstream& file);
    bool corVerifs(unsigned &beg_data_entity, unsigned &end_data_entity, \
		std::vector<std::vector<double>> token_list, bool &cor, unsigned &seg_line, \
		std::vector<double> line);
    bool scaVerifs(std::vector<double> line);
    bool readFile(const std::string &filename);
    bool sauvegarde(std::string nom_sauvegarde = "sauvegarde.txt");
    void execution();
    bool idAlreadyExists(unsigned id);
    bool Collisions(Corail new_cor, Segment new_seg, bool reading);
    void draw_algues();
    void draw_coraux();
    void draw_scavengers();
};


std::ostream& operator<<(std::ostream&, S2d const&);


#endif // SIMULATION_H
