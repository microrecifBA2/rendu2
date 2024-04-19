// lifeform.h par par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>

class Lifeform {
protected:
    S2d position;
    double age;
    bool success; // Changer le type de Success en bool

public:
    Lifeform(S2d position, double age);
    S2d getPosition() const;
    double getAge() const;
    bool lifeformSuccess() const; // Changer le type de retour en bool
};

class Algue : public Lifeform { 
public :
    Algue(double x, double y, double age);
};

class Corail : public Lifeform {
private:
    S2d end;
    unsigned id_cor;
    bool statut_cor;
    bool dir_rot;
    bool statut_dev; 
    unsigned nbseg;
    std::vector<Segment> segments;

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
    double rayon;
    bool statut;
    unsigned corail_id_cible;

public:
    Scavenger(double x, double y, double age, double radius, double status,
        int corail_id_cible = -1);
    double getRadius() const;
    double getStatus() const;
    double getId() const;
};

#endif // LIFEFORM_H
