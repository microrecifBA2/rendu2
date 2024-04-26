// lifeform.cc par 375454 et 376265, version 1.01

#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>

#include "shape.h"
#include "constantes.h"
#include "message.h"
#include "lifeform.h"

using namespace std;


Lifeform::Lifeform(S2d position, double age)
:position(position), age(age), success(true) {
    if (!((position.x >= 1) && (position.x <= dmax - 1) && (position.y >= 1) && \
    (position.y <= dmax - 1))) {
        cout << message::lifeform_center_outside(position.x, position.y);
        success = false;
        return;
    }

    if (age <= 0) {
        cout << message::lifeform_age(age);
        success = false;
        return;
    }
}

S2d Lifeform::getPosition() const {
    return position;
}

double Lifeform::getAge() const {
    return age;
}

void Lifeform::incrementer() {
    age++;
}

bool Lifeform::lifeformSuccess() const {
    return success;
}

void Lifeform::save(fstream& fichier_sauvegarde) {
    fichier_sauvegarde << "\t" << position << " " << to_string(age) << endl;
}

Algue::Algue(double x, double y, double age)
: Lifeform({x, y}, age)
{}

void Algue::draw() {
    draw_circle(1., r_alg, position.x, position.y, GREEN);
}

Corail::Corail(double x, double y, double age, unsigned id, bool statut_cor,
				bool dir_rot, bool statut_dev, unsigned nbseg)
:Lifeform({x, y}, age), id_cor(id), statut_cor(statut_cor), dir_rot(dir_rot),
nbseg(nbseg)
{
    end = position;
}

void Corail::addSegment(Segment seg, bool reading) {
    if (success) {
        double epsil = reading ? 0. : epsil_zero;
        double length(seg.getLength()), angle(seg.getAngle());

        if (seg.is_length_outside() or \
        !((length >= l_repro - l_seg_interne) && (length < l_repro))) {
            cout << message::segment_length_outside(id_cor, length);
            success = false;
            return;
        }

        if (seg.is_angle_outside()) {
            cout << message::segment_angle_outside(id_cor, angle);
            success = false;
            return;
        }

        end = seg.getEnd();

        if (!((end.x > epsil) && (end.x < dmax - epsil) && (end.y > epsil) && \
            (end.y < dmax - epsil))) {
                cout << message::lifeform_computed_outside(id_cor, end.x, end.y);
                success = false;
                return;
        }

        segments.push_back(seg);
    }
}

void Corail::Superposition() {
    if (success) {
        for (unsigned i(0); i < segments.size() - 1; i++) {
            if (angleDev(segments[i], segments[i+1]) == 0.) {
                cout << message::segment_superposition(id_cor, i, i + 1);
                success = false;
                return;
            }
        }
    }
}

unsigned Corail::getId() const{
    return id_cor;
}

bool Corail::getStatut_cor() const {
    return statut_cor;
}

bool Corail::getDir_rot() const {
    return dir_rot;
}

bool Corail::getStatut_dev() const {
    return statut_dev;
}

unsigned Corail::getNbseg() const{
    return nbseg;
}

S2d Corail::getEnd() const {
    return end;
}

vector<Segment> Corail::getSegments() const {
    return segments;
}

void Corail::draw() {
    draw_square(1., d_cor, position.x, position.y, statut_cor? BLUE : BLACK);

    for (auto& segment: segments) {
        double x1 = segment.getOrigin().x;
        double y1 = segment.getOrigin().y;
        double x2= segment.getEnd().x;
        double y2 = segment.getEnd().y;

        draw_line(1., x1, y1, x2, y2, statut_cor? BLUE : BLACK);
    }
}

void Corail::save(fstream& fichier_sauvegarde) {
    Lifeform::save(fichier_sauvegarde);
    fichier_sauvegarde << to_string(id_cor) << " " << to_string(statut_cor) << " " 
                       << to_string(dir_rot) << " " << to_string(statut_dev) << " " 
                       << to_string(nbseg) << endl;
        for (auto& segment: segments) {
            fichier_sauvegarde << "\t \t" << to_string(segment.getAngle()) << " " << \
                to_string(segment.getLength()) << endl;
        }
}

Scavenger::Scavenger(double x, double y, double age, double rayon, double status,
	int corail_id_cible)
:Lifeform({x, y}, age), rayon(rayon), statut(status),
	corail_id_cible(corail_id_cible)
{
    if (success) {
        if (!((rayon >= r_sca) && (rayon < r_sca_repro))) {
            cout << message::scavenger_radius_outside(static_cast<unsigned>(rayon));
            success = false;
            return;
        }
    }
}

double Scavenger::getRadius() const {
    return rayon;
}

double Scavenger::getStatus() const {
    return statut;
}

double Scavenger::getId() const {
    return corail_id_cible;
}

void Scavenger::draw() {
    draw_circle(1., rayon, position.x, position.y, RED);
}

void Scavenger::save(fstream& fichier_sauvegarde) {
    Lifeform::save(fichier_sauvegarde);
    fichier_sauvegarde << " " << to_string(rayon) << " " << to_string(statut);
        if (statut != 0) {
                fichier_sauvegarde << " " << to_string(corail_id_cible);
        }
        fichier_sauvegarde << endl;
}

ostream& operator<<(ostream& sortie, S2d const& point) {
    sortie << to_string(point.x) << " " << to_string(point.y );
    return sortie;
}