// simulation.cc par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

#include "message.h"
#include "simulation.h"
#include "constantes.h"

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

bool Simulation::corVerifs(unsigned& beg_data_entity, \
	unsigned& end_data_entity, vector<vector<double>> token_list, \
	bool& cor, unsigned& seg_line, vector<double> line) {
    if (cor) { // Si on est en train de lire les données générales du corail
        seg_line = 0;
        if (idAlreadyExists(line[3])) {
            cout << message::lifeform_duplicated_id(line[3]);
            return false;
        }

        Corail corail(line[0], line[1], line[2], line[3], line[4], line[5], \
            line[6], line[7]);
        
        if (!corail.lifeformSuccess()) {return false;}

        coraux.push_back(corail);
        
        end_data_entity += static_cast<int>(corail.getNbseg());

        cor = false; // On ne lit plus les informations générales du corail
    }

    else {
        Corail *cur_cor(&coraux.back());
        Segment cur_seg(cur_cor->getEnd(), line[0], line[1]);
        cur_cor->addSegment(cur_seg, true);
        cur_cor->Superposition();
        if (Collisions(*cur_cor, cur_seg, true) == false) {return false;}

        ++seg_line;
        if (seg_line == cur_cor->getNbseg()) {               
            // On lit de nouveau les informations générales d'un nouveau corail
            cor = true;
        }
    }
    return true;
}

bool Simulation::scaVerifs(vector<double> line) {
    if (line[4]) {
        Scavenger scavenger(line[0], line[1], line[2], line[3], line[4],
                            line[5]);
        
        if (!scavenger.lifeformSuccess()) {return false;}

        if (!(idAlreadyExists(line[5]))) {
            cout << message::lifeform_invalid_id(line[5]);
            return false;
        }

        scavengers.push_back(scavenger);
    }
    else {
        Scavenger scavenger(line[0], line[1], line[2], line[3], line[4]);
        scavengers.push_back(scavenger);
    }
    return true;
}


bool Simulation::readFile(const string& filename) {
    coraux.clear();
    algues.clear();
    scavengers.clear();

    bool success(true);
    
    ifstream file(filename);
    if ((!file.is_open()) or (file.fail())) { 
        success = false; 
    }

    //e.seed(1);

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
            if (!algue.lifeformSuccess()) {success = false;}
            algues.push_back(algue);
        }
        else if ((curr == CORAUX) && (line_idx >= beg_data_entity) && \
			(line_idx <= end_data_entity)) {
            if (corVerifs(beg_data_entity, end_data_entity, token_list, cor, \
			seg_line, line) == false) {success = false;}
        }
        else if ((curr == SCAVENGERS) && (line_idx >= beg_data_entity) && \
			(line_idx <= end_data_entity)) {
            if (scaVerifs(line) == false) {success = false;};
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

    if (success == false) {
        coraux.clear();
        algues.clear();
        scavengers.clear();

        return false;
    }
    
    file.close();
    cout << message::success();
    return true;
}

bool Simulation::sauvegarde(string nom_sauvegarde) {
    fstream fichier_sauvegarde;
	fichier_sauvegarde.open(nom_sauvegarde, ios::out);
    
    unsigned nb_alg(0), nb_cor(0), nb_sca(0);
    
    nb_alg = algues.size();
    nb_cor = coraux.size();
    nb_sca = scavengers.size();

    fichier_sauvegarde << to_string(nb_alg) << endl;
    for(auto& algue: algues) {
        fichier_sauvegarde << "\t" << to_string(algue.getPosition().x) << " " << to_string(algue.getPosition().y) << " " << to_string(algue.getAge()) << endl;
    }

    fichier_sauvegarde << endl << to_string(nb_cor) << endl;
    
    for(auto& corail: coraux) {
        fichier_sauvegarde << "\t" << corail.getPosition() << " " << to_string(corail.getAge()) << endl;
        for (auto& segment: corail.getSegments()) {
            fichier_sauvegarde << "\t \t" << to_string(segment.getAngle()) << " " << to_string(segment.getLength()) << endl;
        }
    }

    fichier_sauvegarde << endl << to_string(nb_sca) << endl;

    for(auto& sca: scavengers) {
        fichier_sauvegarde << "\t" << sca.getPosition() << " " << to_string(sca.getAge()) << " " << to_string(sca.getRadius()) << " " << to_string(sca.getStatus());
        if (sca.getStatus() != 0) {
                fichier_sauvegarde << " " << to_string(sca.getId());
        }
        fichier_sauvegarde << endl;
    }

	if (fichier_sauvegarde) {
		fichier_sauvegarde.close(); 
        return 0;
	}

    return 1;
}

// void Simulation::execution(bool naissance_alg, default_random_engine e) {
//     for (auto alg = algues.begin(); alg != algues.end();) {
//         alg->incrementer();
//         if (alg->getAge() >= max_life_alg) {
//             alg = algues.erase(alg);
//         }
//     }

//     if (naissance_alg) {
//         double p(alg_birth_rate);
//         bernoulli_distribution b(p); 
//         if (b(e)) {
//             uniform_real_distribution<double> distribution(0.0, 256.0);
//             default_random_engine generator;
//             double random_x = distribution(generator);
//             double random_y = distribution(generator);
//             Algue algue(0, 0, 0);
//             algues.push_back(algue);
//         }
//     }

// }

bool Simulation::idAlreadyExists(unsigned id) {
    for (const auto &corail : coraux) {
        if (corail.getId() == id) {
            return true;
        }
    }
    return false;
}

bool Simulation::Collisions(Corail new_cor, Segment new_seg, bool reading) {
    unsigned new_cor_id = new_cor.getId();
    for (auto& corail : coraux) { 
        vector<Segment> segment_list(corail.getSegments());

        if ((corail.getId() == new_cor_id) && (segment_list.size() >= 2)) {
            segment_list.pop_back();
            segment_list.pop_back();
	    }

        for (unsigned i(0); i < segment_list.size(); i++) {
            S2d p1(segment_list[i].getOrigin()), q1(segment_list[i].getEnd());
            
            S2d p2(new_seg.getOrigin()), q2(new_seg.getEnd());
            
            if (doIntersect(p1, q1, p2, q2, reading)) {
                cout << message::segment_collision(corail.getId(), i, new_cor_id, \
					new_cor.getSegments().size()-1);
                return false;
            }
        }
    }
    return true;
}

ostream& operator<<(ostream& sortie, S2d const& point) {
    sortie << to_string(point.x) << " " << to_string(point.y );
    return sortie;
}