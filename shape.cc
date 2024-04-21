// shape.cc par Camille Venisse (375454) et Edgar Ruault (376265), version 1.01

#include <cmath>
#include <iostream>

#include "shape.h"

using namespace std;

void S2d::operator=(S2d const& other) {
    x = other.x;
    y = other.y;
}

Segment::Segment(S2d origin, double angle, double length) 
:origin(origin), angle(angle), length(length)
{
    if(!((angle >= -M_PI) and (angle <= M_PI))) {
        angle_outside = true;
    }

    if (length < 0) {
        length_outside = true;
    }

}

S2d Segment::getOrigin() const {
    return origin;
}

S2d Segment::getEnd() const {
    S2d point;
    point.x = origin.x + length * cos(angle);
    point.y = origin.y + length * sin(angle);
    return point;
}

double Segment::getAngle() const {
    return angle;
}

double Segment::getLength() const {
    return length;
}

bool Segment::is_angle_outside() const {
    return angle_outside;
}

bool Segment::is_length_outside() const {
    return length_outside;
}

// Manipulateurs
void Segment::setAngle(double ang) {
    angle = ang;
    if(!((angle >= -M_PI) and (angle <= M_PI))) {
        angle_outside = true;
    }
}

void Segment::setLength(double len) {
    length = len;
    if (length < 0) {
        length_outside = true;
    }
}


double Dist(S2d p, S2d q) {
    return sqrt(pow(p.x - q.x, 2)+ pow(p.y - q.y, 2));
}

double s_product(S2d p, S2d q, S2d r) {
    return (q.x - p.x) * (r.x - p.x) + (q.y - p.y)*(r.y - p.y);
}

double angleDev(const Segment& seg1, const Segment& seg2) {
	double delta = seg1.getAngle() + M_PI - seg2.getAngle();
	if( delta <= M_PI) {
		return delta;
	}
	return delta - 2*M_PI;
}

double orientation(S2d p, S2d q, S2d r, bool reading) {
    double epsil = reading ? 0. : epsil_zero;
    double val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 

    val /= Dist(p, q);
    
    if (fabs(val) < epsil) return 0;
  
    return (val > 0)? 1: 2;
} 

bool onSegment(S2d p, S2d q, S2d r, bool reading) { 
    double epsil = reading ? 0. : epsil_zero;
    double pr_norm = Dist(p, r);
    double x = s_product(p, q, r)/pr_norm;

    if ((-epsil <= x) and (x <= pr_norm + epsil))
        return true;

    return false; 
}

bool doIntersect(S2d p1, S2d q1, S2d p2, S2d q2, bool reading) {
    int o1 = orientation(p1, q1, p2, reading); 
    int o2 = orientation(p1, q1, q2, reading); 
    int o3 = orientation(p2, q2, p1, reading); 
    int o4 = orientation(p2, q2, q1, reading); 
  
    if (o1 != o2 && o3 != o4) 
        return true; 

    if (o1 == 0 && onSegment(p1, p2, q1, reading)) return true; 
  
    if (o2 == 0 && onSegment(p1, q2, q1, reading)) return true; 
  
    if (o3 == 0 && onSegment(p2, p1, q2, reading)) return true; 
  
    if (o4 == 0 && onSegment(p2, q1, q2, reading)) return true; 
  
    return false; 
}


void draw_line(int width_line, double x1, double y1, double x2, double y2, Color couleur) {
    graphic_draw_line(width_line, x1, y1,  x2, y2, couleur);
}

void draw_circle(int width_line, double radius, double x, double y, Color couleur) {
    graphic_draw_circle(width_line, radius, x, y , couleur);
}

void draw_square(int width_line, double side, double x, double y, Color couleur) {
    graphic_draw_square(width_line, side, x, y , couleur);
}