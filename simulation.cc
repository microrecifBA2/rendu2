// simulation.cc par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

#include "message.h"
#include "simulation.h"

using namespace std;

vector<vector<double>> Simulation::storeTokens(ifstream& file) {

    string line;
    vector<vector<double>> token_list;

    while (getline(file >> ws, line)) {
        if ((line.empty()) || (line[0] == '#') || (line[0] == '\r') || \
			(line[0] == '\n') ) {
            continue;
        }

        istringstream line_flow(line);
        vector<double> line_tokens;

        double token;
        while (line_flow >> token) {
            line_tokens.push_back(token);
        }

        if (!line_tokens.empty()) {
            token_list.push_back(line_tokens);
        }
    }
    return token_list;
}

void Simulation::corVerifs(unsigned& beg_data_entity, \
	unsigned& end_data_entity, vector<vector<double>> token_list, \
	bool& cor, unsigned& seg_line, vector<double> line) {
    if (cor){ // Si on est en train de lire les données générales du corail
        seg_line = 0;
        if (idAlreadyExists(line[3])) {
            cout << message::lifeform_duplicated_id(line[3]);
            exit(EXIT_FAILURE);
        }

        Corail corail(line[0], line[1], line[2], line[3], line[4], line[5], \
            line[6], line[7]);

        Coraux.push_back(corail);
        
        end_data_entity += static_cast<int>(corail.getNbseg());

        cor = false; // On ne lit plus les informations générales du corail
    }

    else {
        Corail *cur_cor(&Coraux.back());
        Segment cur_seg(cur_cor->getEnd(), line[0], line[1]);
        cur_cor->addSegment(cur_seg, true);
        cur_cor->Superposition();
        Collisions(*cur_cor, cur_seg, true);

        ++seg_line;
        if (seg_line == cur_cor->getNbseg())
        {               
            // On lit de nouveau les informations générales d'un nouveau corail
            cor = true;
        }
    }
}

void Simulation::scaVerifs(vector<double> line) {
    if (line[4]) {
        Scavenger scavenger(line[0], line[1], line[2], line[3], line[4],
                            line[5]);

        if (!(idAlreadyExists(line[5]))) {
            cout << message::lifeform_invalid_id(line[5]);
            exit(EXIT_FAILURE);
        }

        Scavengers.push_back(scavenger);
    }
    else {
        Scavenger scavenger(line[0], line[1], line[2], line[3], line[4]);
        Scavengers.push_back(scavenger);
    }
}
bool Simulation::readFile(const string& filename) {
    ifstream file(filename);
    if ((!file.is_open()) or (file.fail())) { 
        return 1; 
    }
    vector<vector<double>> token_list(storeTokens(file));
    enum current_type {ALGUES, CORAUX, SCAVENGERS};
    current_type curr(ALGUES);
    unsigned beg_data_entity = 1, end_data_entity = token_list[0][0];
    unsigned line_idx(0);
    unsigned seg_line(0); // Curseur pour la lecture des données propres aux segments
    bool cor(true); // Données générales du corail ou de ses segments

    for (const auto& line : token_list) {
        if ((curr == ALGUES) && (line_idx >= beg_data_entity) &&
            (line_idx <= end_data_entity)){
            Algue algue(line[0], line[1], line[2]);
            Algues.push_back(algue);
        }
        else if ((curr == CORAUX) && (line_idx >= beg_data_entity) && \
			(line_idx <= end_data_entity)) {
            corVerifs(beg_data_entity, end_data_entity, token_list, cor, \
			seg_line, line);
        }
        else if ((curr == SCAVENGERS) && (line_idx >= beg_data_entity) && \
			(line_idx <= end_data_entity)) {
            scaVerifs(line);
        }
        if (line_idx == end_data_entity) {
            if (curr == ALGUES) {curr = CORAUX;}
            else if (curr == CORAUX) {curr = SCAVENGERS;}
            else if (curr == SCAVENGERS) {break;}
            beg_data_entity = end_data_entity + 2;
            end_data_entity = beg_data_entity + token_list[beg_data_entity - 1][0]-1;
        }
        line_idx++;
    }
    file.close();
    cout << message::success();
    exit(0);
}

bool Simulation::idAlreadyExists(unsigned id) {
    for (const auto &corail : Coraux)
    {
        if (corail.getId() == id) {
            return true;
        }
    }
    return false;
}

void Simulation::Collisions(Corail new_cor, Segment new_seg, bool reading) {
    unsigned new_cor_id = new_cor.getId();
    for (auto& corail : Coraux) { 
        vector<Segment> segment_list(corail.getSegments());

        if ((corail.getId() == new_cor_id) && (segment_list.size() >= 2)) {
            segment_list.pop_back();
            segment_list.pop_back();
	    }

        for (unsigned i(0); i < segment_list.size(); i++) {
            S2d p1(segment_list[i].getOrigin()), q1(segment_list[i].getEnd());
            
            S2d p2(new_seg.getOrigin()), q2(new_seg.getEnd());
            
            if (doIntersect(p1, q1, p2, q2, reading))
            {
                cout << message::segment_collision(corail.getId(), i, new_cor_id, \
					new_cor.getSegments().size()-1);
                exit(EXIT_FAILURE);
            }
        }
    }
}

ostream& operator<<(ostream& sortie, S2d const& point) {
    sortie << "(" << point.x << "," << point.y << ")";
    return sortie;
}