// gui.h par Camille Venisse (375454) et Edgar Ruault (376265), version 2.0

#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/eventcontrollerkey.h>
#include <glibmm/main.h>

#include "graphic_gui.h"
#include "simulation.h"

constexpr unsigned taille_dessin(500);

struct Frame { // Model Framing and window parameters
	double xMin; // frame parameters
	double xMax;
	double yMin;
	double yMax;
	double asp;  // frame aspect ratio
	double height;  // window height
	double width;   // window width
};

class MyArea : public Gtk::DrawingArea {
public:
	MyArea(Simulation* simulation);
	virtual ~MyArea();

protected:
	Simulation* simulation;
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
	void setFrame(Frame x); 
    void adjustFrame(int width, int height);

private:
    Frame frame;
};

class MyEvent : public Gtk::Window {
public:
	MyEvent(Simulation simulation_);
protected:
	Simulation simulation;
	//Button Signal handlers:
	void on_button_clicked_exit();
	void on_button_clicked_open();
	void on_button_clicked_save();
	void on_button_clicked_start();
	void on_button_clicked_step();
	void on_check_button_toggled();
	bool on_key_press_event(guint keyval, guint keycode, Gdk::ModifierType state);
	void on_file_dialog_response(int button_type, Gtk::FileChooserDialog* dialog);
	bool on_timeout(bool nouv_sim);

	bool started = false;
	bool timer_added;
	bool disconnect;
	const int timeout_value = 25;	

	MyArea m_Area;

	Gtk::Box m_Main_Box, m_Interface_Box, m_Infos_Box, \
		m_Buttons_Box, m_maj_Box, m_AlgCount_Box, m_CorCount_Box, m_ScaCount_Box;

	Gtk::Button m_Button_Exit, m_Button_Open, m_Button_Save, m_Button_Start, \
		m_Button_Step;
		
	Gtk::CheckButton m_CheckButton_Algues;
	
	Gtk::Label m_Label_General, m_Label_Infos, m_Label_NbMaj, m_Label_Alg, \
		m_Label_Cor, m_Label_Sca, timer_data, nb_alg, nb_cor, nb_sca;

	Gtk::Separator separateur;
};

#endif // GUI_H