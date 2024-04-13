#include "gui.h"
#include <cairomm/context.h>
#include <gtkmm/label.h>
#include <iostream>

constexpr int area_side(200);

MyArea::MyArea(): empty(false)
{
	set_content_width(area_side);
	set_content_height(area_side);
	
}

MyArea::~MyArea()
{
}



MyEvent::MyEvent():
	m_Main_Box(Gtk::Orientation::HORIZONTAL, 0),
	m_Interface_Box(Gtk::Orientation::VERTICAL, 2),
	m_Buttons_Box(Gtk::Orientation::VERTICAL, 6),
	m_Infos_Box(Gtk::Orientation::VERTICAL, 4),
	m_Label_General("General"),
	m_Button_Exit("exit"),
	m_Button_Open("open"),
	m_Button_Save("save"),
	m_Button_Start("start"),
	m_Button_Step("step"),
	m_CheckButton_Algues("Naissance d'algues"),
	m_Label_Infos("Info : nombre de ..."),
	m_AlgCount_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_CorCount_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_ScaCount_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_Label_Alg("algues: "),
	m_Label_Cor("coraux: "),
	m_Label_Sca("charognards: ")
{
	set_resizable(false);
	set_child(m_Main_Box);

	m_Main_Box.append(m_Interface_Box);
	m_Main_Box.append(m_Area);
	m_Interface_Box.append(m_Buttons_Box);
	m_Interface_Box.append(m_Infos_Box);
	
	m_Buttons_Box.append(m_Label_General);
	m_Buttons_Box.append(m_Button_Exit);
	m_Buttons_Box.append(m_Button_Open);
	m_Buttons_Box.append(m_Button_Save);
	m_Buttons_Box.append(m_Button_Start);
	m_Buttons_Box.append(m_Button_Step);
	m_Buttons_Box.append(m_CheckButton_Algues);


	m_Infos_Box.append(m_Label_Infos);
	m_Infos_Box.append(m_AlgCount_Box);
	m_Infos_Box.append(m_CorCount_Box);
	m_Infos_Box.append(m_ScaCount_Box);

	m_AlgCount_Box.append(m_Label_Alg);
	m_CorCount_Box.append(m_Label_Cor);
	m_ScaCount_Box.append(m_Label_Sca);

	
	m_Button_Exit.signal_clicked().connect(
		sigc::mem_fun(*this, &MyEvent::on_button_clicked_exit));
		
}

void MyEvent::on_button_clicked_exit()
{
	exit(EXIT_SUCCESS);
}

