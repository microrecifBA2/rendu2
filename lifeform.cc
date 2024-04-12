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
:Position(position), Age(age)
{
    if (!((position.x >= 1) && (position.x <= dmax - 1) && (position.y >= 1) && (position.y <= dmax - 1)))
    {
        cout << message::lifeform_center_outside(position.x, position.y);
        exit(EXIT_FAILURE);
    }

    if (Age <= 0) {
        cout << message::lifeform_age(static_cast<int>(Age));
        exit(EXIT_FAILURE);
    }
}

Algue::Algue(double x, double y, double age)
: Lifeform({x, y}, age)
{}


Corail::Corail(double x, double y, double age, unsigned id, bool statut_cor,
				bool dir_rot, bool statut_dev, unsigned nbseg)
:Lifeform({x, y}, age), Id_cor(id), Statut_cor(statut_cor), Dir_rot(dir_rot),
Nbseg(nbseg)
{
    End = Position;
}

void Corail::addSegment(Segment seg, bool reading) {
    double epsil = reading ? 0. : epsil_zero;
    double length(seg.getLength()), angle(seg.getAngle());

    if (seg.is_length_outside() or \
    !((length >= l_repro - l_seg_interne) && (length < l_repro))) {
        cout << message::segment_length_outside(Id_cor, length);
        exit(EXIT_FAILURE);
    }

    if (seg.is_angle_outside()) {
        cout << message::segment_angle_outside(Id_cor, angle);
        exit(EXIT_FAILURE);
    }

    End = seg.getEnd();

    if (!((End.x > epsil) && (End.x < dmax - epsil) && (End.y > epsil) && \
		(End.y < dmax - epsil))) {
            cout << message::lifeform_computed_outside(Id_cor, End.x, End.y);
            exit(EXIT_FAILURE);
    }

    Segments.push_back(seg);
}

unsigned Corail::getNbseg() const{
    return Nbseg;
}

unsigned Corail::getId() const{
    return Id_cor;
}

S2d Corail::getEnd() const {
    return End;
}

vector<Segment> Corail::getSegments() const {
    return Segments;
}

void Corail::Superposition() {
    for (unsigned i(0); i < Segments.size() - 1; i++)
    {
        if (angleDev(Segments[i], Segments[i+1]) == 0.) {
            cout << message::segment_superposition(Id_cor, i, i + 1);
            exit(EXIT_FAILURE);
        }
    }
}

Scavenger::Scavenger(double x, double y, double age, double rayon, double status,
	int corail_id_cible)
:Lifeform({x, y}, age), Rayon(rayon), Statut(status),
	Corail_id_cible(corail_id_cible)
{
    if (!((Rayon >= r_sca) && (Rayon < r_sca_repro)))
    {
        cout << message::scavenger_radius_outside(static_cast<unsigned int>(Rayon));
        exit(EXIT_FAILURE);
    }
}
