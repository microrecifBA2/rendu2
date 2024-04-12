// shape.h par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#ifndef SHAPE_H
#define SHAPE_H

constexpr double epsil_zero(0.5) ;


struct S2d {
    double x = 0.;
    double y = 0.;
    void operator=(S2d const& other);
};


class Segment {
private:
    S2d Origin;
    double Angle;
    double Length;
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



#endif // SHAPE_H
