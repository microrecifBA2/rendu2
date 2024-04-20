#include <cairomm/context.h>
#include <gtkmm/label.h>
#include <iostream>

#include "gui.h"

constexpr unsigned taille_dessin(500);

static Frame default_frame = {-150., 150., -100., 100., 1.5, taille_dessin, taille_dessin};

static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame);
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame);


MyArea::MyArea(Simulation* simulation)
:simulation(simulation)
{
	set_content_width(taille_dessin);
	set_content_height(taille_dessin);
	set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
	graphic_set_context(cr);

	adjustFrame(width, height);
	draw_frame(cr, frame);              // drawing the drawingArea space
	
	orthographic_projection(cr, frame); // set the transformation MODELE to GTKmm

	simulation->draw_algues();
	simulation->draw_coraux();
	simulation->draw_scavengers();

}

void MyArea::setFrame(Frame f)
{
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
} 

void MyArea::adjustFrame(int width, int height)
{
	frame.width  = width;
	frame.height = height;

	// Preventing distorsion by adjusting the frame (cadrage)
	// to have the same proportion as the graphical area
	
    // use the reference framing as a guide for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp)
    { // keep yMax and yMin. Adjust xMax and xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else
    { // keep xMax and xMin. Adjust yMax and yMin
	    frame.xMax = default_frame.xMax ;
	    frame.xMin = default_frame.xMin ;
	  	  
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
        // the new frame is centered on the mid-point along Y
	    frame.yMax = mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}


MyEvent::MyEvent(Simulation simulation_):
	simulation(simulation_),
	m_Area(&simulation),
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

	m_Button_Open.signal_clicked().connect(
		sigc::mem_fun(*this, &MyEvent::on_button_clicked_open));

	m_Button_Save.signal_clicked().connect(
		sigc::mem_fun(*this, &MyEvent::on_button_clicked_save));
	
	m_Button_Start.signal_clicked().connect(
		sigc::mem_fun(*this, &MyEvent::on_button_clicked_start));

	m_Button_Step.signal_clicked().connect(
		sigc::mem_fun(*this, &MyEvent::on_button_clicked_step));

	//signal_key_press_event().connect(sigc::mem_fun(*this, &MyArea::on_key_press_event));
}

/*void MyEvent::on_key_press_event(GdkEventKey* event) {
	if (event->keyval == GDK_KEY_s) {
		myEvent.on_button_clicked_start();
	}
	else if (event->keyval == GDK_KEY_1) {
		myEvent.on_button_clicked_step();
	}
}*/

void MyEvent::on_button_clicked_exit() {
	exit(EXIT_SUCCESS);
}

void MyEvent::on_button_clicked_open() {
	//on_file_dialog_response(response_id=1);
	// lire un fichier avec GTKmm pour initialiser une simulation avec detection d’erreur
	
}

void MyEvent::on_button_clicked_save() {
	// sauvegarder l’état courant de la simulation (éventuellement vide) dans un fichier dont le nom
	// est fourni à GTKmm
}

void MyEvent::on_button_clicked_start() {
	/*if (started == true) {
		started = false;
		m_Button_Start.set_label("start");
	}
	else {
		started = true;
		m_Button_Start.set_label("stop");
	}
	// déclenché avec bouton start ou touche "s"

	/* le label du bouton devient “stop” et un timer est lancé qui produit l’affichage d’un compteur
	entier qui progresse d’une unité à chaque execution du signal handler du timer. Cela permet de simuler
	l’appel d’une mise à jour de la simulation. Si on re-clique sur le bouton (qui maintenant affiche “stop”)
	alors le timer s’arrête et le label redevient “start” */
}

void MyEvent::on_button_clicked_step() {
	//step = true;

	// déclenché avec bouton step ou touche "1"

	/*
	 l’action de ce bouton est seulement prise en compte quand la simulation n’est pas en cours
	d’exécution (c’est à dire quand on voit le label “start” au-dessus du bouton “step”). Dans ce contexte, un
	clic sur ce bouton produit UNE SEULE mise à jour de la simulation. Cela est simulé en faisant afficher une
	seule incrémentation du compteur utilisé par le timer
	*/
}


static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame)
{
	//display a rectangular frame around the drawing area
	cr->set_line_width(10.0);
	// draw greenish lines
	cr->set_source_rgb(0., 0.7, 0.2);
	cr->rectangle(0,0, frame.width, frame.height);
	cr->stroke();
}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame)
{
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), -frame.height/(frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}
