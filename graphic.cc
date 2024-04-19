#include "graphic_gui.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr) { 
    ptcr = &cr;
}

void graphic_draw_line(const int width, double x1, double y1, double x2, double y2, Color couleur) { 
    (*ptcr)->set_line_width(width);

    switch (couleur) {
    case BLUE: (*ptcr)->set_source_rgb(0., 0., 1.); break;
    case BLACK: (*ptcr)->set_source_rgb(1., 1., 1.); break;
    }

    (*ptcr)->move_to(x1, y1);
    (*ptcr)->line_to(x2, y2);
    (*ptcr)->stroke();
}