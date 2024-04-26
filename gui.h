#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/separator.h>
#include <gtkmm.h>

#include "graphic_gui.h"
#include "simulation.h"

constexpr unsigned taille_dessin(500);

struct Frame // Model Framing and window parameters
{
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

	Gtk::Box m_Main_Box, m_Interface_Box;
	Gtk::Box m_Infos_Box;
	Gtk::Box m_Buttons_Box;
	Gtk::Box m_maj_Box;
	Gtk::Box m_AlgCount_Box;
	Gtk::Box m_CorCount_Box;
	Gtk::Box m_ScaCount_Box;

	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;
	Gtk::Button m_Button_Start;
	Gtk::Button m_Button_Step;
	Gtk::CheckButton m_CheckButton_Algues;
	
	Gtk::Label m_Label_General;
	Gtk::Label m_Label_Infos;
	Gtk::Label m_Label_NbMaj;
	Gtk::Label m_Label_Alg;
	Gtk::Label m_Label_Cor;
	Gtk::Label m_Label_Sca;
	Gtk::Label timer_data;
	Gtk::Label nb_alg;
	Gtk::Label nb_cor;
	Gtk::Label nb_sca;

	Gtk::Separator separateur;
};

#endif // GUI_H
