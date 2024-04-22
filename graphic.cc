#include "graphic_gui.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr) { 
    ptcr = &cr;
}

void graphic_draw_line(int width_line, double x1, double y1, double x2, double y2, Color couleur) { 
    (*ptcr)->set_line_width(width_line);

    switch (couleur) {
    case GREY:
    case GREEN:
    case RED:
    case BLACK: (*ptcr)->set_source_rgb(0., 0., 0.); break;
    case BLUE: (*ptcr)->set_source_rgb(0., 0., 1.); break;
    }

    (*ptcr)->move_to(x1, y1);
    (*ptcr)->line_to(x2, y2);
    (*ptcr)->stroke();
}


void graphic_draw_circle(int width_line, double radius, double x, double y, Color couleur) {
    (*ptcr)->set_line_width(width_line);

    switch (couleur) {
    case BLUE:
    case BLACK:
    case GREY:
    case GREEN: (*ptcr)->set_source_rgb(0., 1., 0.); break;
    case RED: (*ptcr)->set_source_rgb(1., 0., 0.); break;
    }

    (*ptcr)->arc(x, y, radius, 0., 2.0 * M_PI);
    (*ptcr)->stroke();

}


void graphic_draw_square(int width_line, double side, double x, double y, Color couleur) {
    (*ptcr)->set_line_width(width_line);

    switch (couleur) {
    case GREEN:
    case RED:
    case BLACK:
    case GREY: (*ptcr)->set_source_rgb(0.5, 0.5, 0.5); break;
    case BLUE: (*ptcr)->set_source_rgb(0., 0., 1.); break;
    }

    (*ptcr)->rectangle(x - side/2, y - side/2, side, side);
    (*ptcr)->stroke();
}
