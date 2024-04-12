// simulation.h par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#ifndef SIMULATION_H
#define SIMULATION_H

#include "shape.h"
#include "lifeform.h"


class Simulation{
private:
    std::string filename;
    std::vector<Corail> Coraux;
    std::vector<Algue> Algues;
    std::vector<Scavenger> Scavengers;

public:
    std::vector<std::vector<double>> storeTokens(std::ifstream& file);
    void corVerifs(unsigned &beg_data_entity, unsigned &end_data_entity, \
		std::vector<std::vector<double>> token_list, bool &cor, unsigned &seg_line, \
		std::vector<double> line);
    void scaVerifs(std::vector<double> line);
    bool readFile(const std::string &filename);
    bool idAlreadyExists(unsigned id);
    void Collisions(Corail new_cor, Segment new_seg, bool reading);
};


std::ostream& operator<<(std::ostream&, S2d const&);


#endif // SIMULATION_H
