// shape.h par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#ifndef SHAPE_H
#define SHAPE_H

#include "graphic.h"

constexpr double epsil_zero(0.5) ;


struct S2d {
    double x = 0.;
    double y = 0.;
    void operator=(S2d const& other);
};


class Segment {
private:
    S2d origin;
    double angle;
    double length;
    bool length_outside = false;
    bool angle_outside = false;
public:
    Segment(S2d origin, double angle, double length);
    Segment() = default;
    S2d getOrigin() const;
    S2d getEnd() const;
    double getAngle() const;
    double getLength() const;
    bool is_angle_outside() const;
    bool is_length_outside() const;
    void setAngle(double angle);
    void setLength(double length);
};

double angleDev(const Segment& seg1, const Segment& seg2);
double Dist(S2d p, S2d q);
double s_product(S2d p, S2d q, S2d r);

double orientation(S2d p, S2d q, S2d r, bool reading);
bool onSegment(S2d p, S2d q, S2d r, bool reading); 
bool doIntersect(S2d p1, S2d q1, S2d p2, S2d q2, bool reading);

void draw_line(int width, double x1, double y1, double x2, double y2, Color couleur);
void draw_circle(int width_line, double radius, double x, double y, Color couleur);
void draw_square(int width_line, double side, double x, double y, Color couleur);
#endif // SHAPE_H
