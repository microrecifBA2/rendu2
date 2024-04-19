#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color
{
    BLACK,
    RED,
    GREEN,
    BLUE,
};

void graphic_draw_line(const int width, double x1, double y1, double x2, double y2, Color couleur);

#endif //GRAPHIC_H