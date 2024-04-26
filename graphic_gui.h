// graphic_gui.h par Camille Venisse (375454) et Edgar Ruault (376265), version 2.0

#ifndef GRAPHIC_GUI_H
#define GRAPHIC_GUI_H

#include <gtkmm/drawingarea.h>
#include "graphic.h"

void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr);

#endif // GRAPHIC_GUI_H