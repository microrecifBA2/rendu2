#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color {
    BLACK,
    RED,
    GREEN,
    BLUE,
    GREY
};

void graphic_draw_line(int width_line, double x1, double y1, double x2, double y2, 
    Color couleur);
void graphic_draw_circle(int width_line, double radius, double x, double y, 
    Color couleur);
void graphic_draw_square(int width_line, double side, double x, double y, 
    Color couleur);

#endif //GRAPHIC_H