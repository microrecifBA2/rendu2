// lifeform.h par par Camille Venisse (375454) et Edgar Ruault (376265), version 2.0

#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>
#include <fstream>

class Lifeform {
protected:
    S2d position;
    double age;
    bool success;

public:
    Lifeform(S2d position, double age);
    S2d getPosition() const;
    double getAge() const;
    void incrementer();
    bool lifeformSuccess() const;
    virtual void save(std::fstream& fichier_sauvegarde);
};

class Algue : public Lifeform { 
public :
    Algue(double x, double y, double age);
    void draw();
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
    unsigned getId() const;
    bool getStatut_cor() const;
    bool getDir_rot() const;
    bool getStatut_dev() const;
    unsigned getNbseg() const;
    S2d getEnd() const;
    std::vector<Segment> getSegments() const;
    void draw();
    void save(std::fstream& fichier_sauvegarde) override;
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
    void draw();
    void save(std::fstream& fichier_sauvegarde) override;
};

std::ostream& operator<<(std::ostream& sortie, S2d const& point);

#endif // LIFEFORM_H
