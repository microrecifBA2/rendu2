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
:position(position), age(age), success(true)
{
    if (!((position.x >= 1) && (position.x <= dmax - 1) && (position.y >= 1) && (position.y <= dmax - 1)))
    {
        cout << message::lifeform_center_outside(position.x, position.y);
        success = false;
    }

    if (age <= 0) {
        cout << message::lifeform_age(age);
        success = false;
    }
}

bool Lifeform::lifeformSuccess() const {
    return success;
}

Algue::Algue(double x, double y, double age)
: Lifeform({x, y}, age)
{}

S2d Lifeform::getPosition() const {
    return position;
}

double Lifeform::getAge() const {
    return age;
}

void Lifeform::incrementer() {
    age++;
}

Corail::Corail(double x, double y, double age, unsigned id, bool statut_cor,
				bool dir_rot, bool statut_dev, unsigned nbseg)
:Lifeform({x, y}, age), id_cor(id), statut_cor(statut_cor), dir_rot(dir_rot),
nbseg(nbseg)
{
    end = position;
}

void Corail::addSegment(Segment seg, bool reading) {
    double epsil = reading ? 0. : epsil_zero;
    double length(seg.getLength()), angle(seg.getAngle());

    if (seg.is_length_outside() or \
    !((length >= l_repro - l_seg_interne) && (length < l_repro))) {
        cout << message::segment_length_outside(id_cor, length);
        success = false;
    }

    if (seg.is_angle_outside()) {
        cout << message::segment_angle_outside(id_cor, angle);
        success = false;
    }

    end = seg.getEnd();

    if (!((end.x > epsil) && (end.x < dmax - epsil) && (end.y > epsil) && \
		(end.y < dmax - epsil))) {
            cout << message::lifeform_computed_outside(id_cor, end.x, end.y);
            success = false;
    }

    segments.push_back(seg);
}

unsigned Corail::getNbseg() const{
    return nbseg;
}

unsigned Corail::getId() const{
    return id_cor;
}

S2d Corail::getEnd() const {
    return end;
}

vector<Segment> Corail::getSegments() const {
    return segments;
}

void Corail::Superposition() {
    for (unsigned i(0); i < segments.size() - 1; i++)
    {
        if (angleDev(segments[i], segments[i+1]) == 0.) {
            cout << message::segment_superposition(id_cor, i, i + 1);
            success = false;
        }
    }
}

Scavenger::Scavenger(double x, double y, double age, double rayon, double status,
	int corail_id_cible)
:Lifeform({x, y}, age), rayon(rayon), statut(status),
	corail_id_cible(corail_id_cible)
{
    if (!((rayon >= r_sca) && (rayon < r_sca_repro)))
    {
        cout << message::scavenger_radius_outside(static_cast<unsigned int>(rayon));
        success = false;
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
