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

void MyEvent::on_button_clicked_open()
{
	// lire un fichier avec GTKmm pour initialiser une simulation avec detection d’erreur
}

void MyEvent::on_button_clicked_save()
{
	// sauvegarder l’état courant de la simulation (éventuellement vide) dans un fichier dont le nom
	// est fourni à GTKmm
}

void on_button_clicked_start()
{
	// déclenché avec bouton start ou touche "s"

	/* le label du bouton devient “stop” et un timer est lancé qui produit l’affichage d’un compteur
	entier qui progresse d’une unité à chaque execution du signal handler du timer. Cela permet de simuler
	l’appel d’une mise à jour de la simulation. Si on re-clique sur le bouton (qui maintenant affiche “stop”)
	alors le timer s’arrête et le label redevient “start” */
}

void on_button_clicked_stop()
{
	// cf bouton start
}

void on_button_clicked_step()
{	
	// déclenché avec bouton step ou touche "1"
	
	/*
	 l’action de ce bouton est seulement prise en compte quand la simulation n’est pas en cours
	d’exécution (c’est à dire quand on voit le label “start” au-dessus du bouton “step”). Dans ce contexte, un
	clic sur ce bouton produit UNE SEULE mise à jour de la simulation. Cela est simulé en faisant afficher une
	seule incrémentation du compteur utilisé par le timer
	*/
}
