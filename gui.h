#ifndef GTKMM_MY_EVENT_H
#define GTKMM_MY_EVENT_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>

class MyArea : public Gtk::DrawingArea
{
public:
	MyArea();
	virtual ~MyArea();
	

protected:
//	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

private:
	bool empty;
};

class MyEvent : public Gtk::Window
{
public:
	MyEvent();

protected:
	//Button Signal handlers:
	void on_button_clicked_exit();

	MyArea m_Area;

	Gtk::Box m_Main_Box;
	Gtk::Box m_Interface_Box;
	Gtk::Box m_Buttons_Box;
	Gtk::Box m_Infos_Box;
	Gtk::Label m_Label_General;
	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;
	Gtk::Button m_Button_Start;
	Gtk::Button m_Button_Step;
	Gtk::CheckButton m_CheckButton_Algues;
	Gtk::Label m_Label_Infos;
	Gtk::Box m_maj_Box;
	Gtk::Box m_AlgCount_Box;
	Gtk::Box m_CorCount_Box;
	Gtk::Box m_ScaCount_Box;
	Gtk::Label m_Label_Alg;
	Gtk::Label m_Label_Cor;
	Gtk::Label m_Label_Sca;

};

#endif // GTKMM_MY_EVENT_H
