#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    GREY
};

void graphic_draw_line(int width, double x1, double y1, double x2, double y2, Color couleur);
void graphic_draw_circle(int width, double radius, double x, double y, Color couleur);
void graphic_draw_square(int width, double side, double x, double y, Color couleur);

#endif //GRAPHIC_H