// lifeform.h par par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>

class Lifeform {
    protected :
        S2d Position;
        double Age;
    public:
        Lifeform(S2d position, double age);
};

class Algue : public Lifeform { 
public :
    Algue(double x, double y, double age);
};

class Corail : public Lifeform {
private:
    S2d End;
    unsigned Id_cor;
    bool Statut_cor;
    bool Dir_rot;
    bool Statut_dev; 
    unsigned Nbseg;
    std::vector<Segment> Segments;

public:
    Corail(double x, double y, double age, unsigned id, bool statut_cor, bool dir_rot,
		bool statut_dev, unsigned nbseg);
    void addSegment(Segment seg, bool reading);
    void Superposition();
    unsigned getNbseg() const;
    unsigned getId() const;
    S2d getEnd() const;
    std::vector<Segment> getSegments() const ;
};

class Scavenger : public Lifeform {
private:
    double Rayon;
    bool Statut;
    unsigned Corail_id_cible;

public:
    Scavenger(double x, double y, double age, double radius, double status,
        int corail_id_cible = -1);
};

#endif // LIFEFORM_H
