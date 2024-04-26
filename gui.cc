// gui.cc par Camille Venisse (375454) et Edgar Ruault (376265), version 2.0
// 375454 (50%), 376265 (50%)

#include <cairomm/context.h>
#include <gtkmm/label.h>
#include <iostream>

#include "gui.h"
#include "constantes.h"


static Frame default_frame = {0., dmax, 0., dmax, 1.0, dmax/2, dmax/2}; 
static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame);
static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
	Frame frame);
	
MyArea::MyArea(Simulation* simulation)
:simulation(simulation) {
	setFrame(default_frame);
	set_content_width(taille_dessin);
	set_content_height(taille_dessin);
	set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea() {}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
	graphic_set_context(cr);

	adjustFrame(width, height);
	orthographic_projection(cr, frame); // set the transformation MODELE to GTKmm

	draw_frame(cr, frame); 

	simulation->draw_algues();
	simulation->draw_coraux();
	simulation->draw_scavengers();

}

void MyArea::setFrame(Frame f) {
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0))
	{
		f.asp = f.width/f.height;
		frame = f;
	}
	else
		std::cout << "incorrect Model framing or window parameters" << std::endl;
} 

void MyArea::adjustFrame(int width, int height) {
	frame.width  = width;
	frame.height = height;

	// Preventing distorsion by adjusting the frame (cadrage)
	// to have the same proportion as the graphical area
	
    // use the reference framing as a guide for preventing distortion
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp) {
		// keep yMax and yMin. Adjust xMax and xMin
	    frame.yMax = default_frame.yMax ;
	    frame.yMin = default_frame.yMin ;	
	  
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
        // the new frame is centered on the mid-point along X
	    frame.xMax = mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    }
    else {
		// keep xMax and xMin. Adjust yMax and yMin
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
	simulation(simulation_), m_Area(&simulation),
	m_Main_Box(Gtk::Orientation::HORIZONTAL, 0),
	m_Interface_Box(Gtk::Orientation::VERTICAL, 2),
	m_Infos_Box(Gtk::Orientation::VERTICAL, 4),
	m_Buttons_Box(Gtk::Orientation::VERTICAL, 6),
	m_maj_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_AlgCount_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_CorCount_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_ScaCount_Box(Gtk::Orientation::HORIZONTAL, 2),
	m_Button_Exit("exit"), m_Button_Open("open"), m_Button_Save("save"),
	m_Button_Start("start"), m_Button_Step("step"),
	m_CheckButton_Algues("Naissance d'algues"), m_Label_General("General"),
	m_Label_Infos("Info : nombre de ..."), m_Label_NbMaj("mise à jour: "),
	m_Label_Alg("algues: "), m_Label_Cor("coraux: "),
	m_Label_Sca("charognards: "), timer_data("0"),
	nb_alg(std::to_string(simulation.nb_alg())),
	nb_cor(std::to_string(simulation.nb_cor())),
	nb_sca(std::to_string(simulation.nb_sca()))
{
	set_child(m_Main_Box);

	set_title("Microrécif");

	m_Main_Box.append(m_Interface_Box);
	m_Main_Box.append(m_Area);
	m_Interface_Box.append(m_Buttons_Box);
	m_Interface_Box.append(separateur);
	m_Interface_Box.append(m_Infos_Box);
	
	m_Buttons_Box.append(m_Label_General);
	m_Buttons_Box.append(m_Button_Exit);
	m_Buttons_Box.append(m_Button_Open);
	m_Buttons_Box.append(m_Button_Save);
	m_Buttons_Box.append(m_Button_Start);
	m_Buttons_Box.append(m_Button_Step);
	m_Buttons_Box.append(m_CheckButton_Algues);

	m_Infos_Box.append(m_Label_Infos);
	m_Infos_Box.append(m_maj_Box);
	m_Infos_Box.append(m_AlgCount_Box);
	m_Infos_Box.append(m_CorCount_Box);
	m_Infos_Box.append(m_ScaCount_Box);

	m_maj_Box.append(m_Label_NbMaj);
	m_maj_Box.append(timer_data);
	m_AlgCount_Box.append(m_Label_Alg);
	m_AlgCount_Box.append(nb_alg);
	m_CorCount_Box.append(m_Label_Cor);
	m_CorCount_Box.append(nb_cor);
	m_ScaCount_Box.append(m_Label_Sca);
	m_ScaCount_Box.append(nb_sca);
	
	m_Area.set_expand();

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

	m_CheckButton_Algues.signal_toggled().connect(
		sigc::mem_fun(*this, &MyEvent::on_check_button_toggled));

	auto controller = Gtk::EventControllerKey::create();
	controller->signal_key_pressed().connect(sigc::mem_fun(*this, \
		&MyEvent::on_key_press_event), false);
    add_controller(controller);
}

bool MyEvent::on_key_press_event(guint keyval, guint keycode, Gdk::ModifierType state){
	switch (keyval) {
		case GDK_KEY_s:
			on_button_clicked_start();
			break;
		case GDK_KEY_1:
			on_button_clicked_step();
			break;
	}
	return true;
}

void MyEvent::on_button_clicked_exit() {
	exit(EXIT_SUCCESS);
}

void MyEvent::on_button_clicked_open() {
	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
		  Gtk::FileChooser::Action::OPEN);

	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &MyEvent::on_file_dialog_response), dialog));
	
	//Add response buttons to the dialog:
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Open", Gtk::ResponseType::OK);
	
	//Add filters, so that only certain file types can be selected:
	
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);

	dialog->show();
	
	
}

void MyEvent::on_button_clicked_save() {
	auto dialog = new Gtk::FileChooserDialog("Please choose a file",
		  Gtk::FileChooser::Action::SAVE);

	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	sigc::mem_fun(*this, &MyEvent::on_file_dialog_response), dialog));
	
	//Add response buttons to the dialog:
	dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Save", Gtk::ResponseType::OK);
	
	//Add filters, so that only certain file types can be selected:
	
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);

	dialog->show();
}

void MyEvent::on_button_clicked_start() {
	if (started == false) {
		started = true;
		m_Button_Start.set_label("stop");
		if(not timer_added) {
			sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
													&MyEvent::on_timeout),false);
			
			auto conn = Glib::signal_timeout().connect(my_slot,timeout_value);
				
			timer_added = true;
		}
	}

	else {
		started = false;
		m_Button_Start.set_label("start");

		if (timer_added) {
			disconnect  = true;   
			timer_added = false;
		}
	}
}

void MyEvent::on_button_clicked_step() {
	if (!started) {
		on_timeout(false);
	}
}

void MyEvent::on_check_button_toggled() {
	if (m_CheckButton_Algues.get_active()) {
        simulation.naissance_alg = true;
    } else {
        simulation.naissance_alg = false;
    }
}


bool MyEvent::on_timeout(bool nouv_sim)
{
	static unsigned int val(1);
	if (disconnect) {
		disconnect = false;
		return false;
	}

	if (nouv_sim) {
		val = 1;
		return true;
	}
	
	timer_data.set_text(std::to_string(val));

	++val;

	simulation.execution();
	nb_alg.set_text(std::to_string(simulation.nb_alg()));
	nb_cor.set_text(std::to_string(simulation.nb_cor()));
	nb_sca.set_text(std::to_string(simulation.nb_sca()));

	m_Area.queue_draw();
	return true; 
}

void MyEvent::on_file_dialog_response (int response_id, \
	Gtk::FileChooserDialog* dialog) {
	if (response_id == Gtk::ResponseType::OK) {
		auto filename = dialog->get_file()->get_path();
		
		Gtk::FileChooser::Action action = dialog->get_action();
		if (action == Gtk::FileChooser::Action::OPEN) {
			simulation.readFile(filename);
			nb_alg.set_text(std::to_string(simulation.nb_alg()));
			nb_cor.set_text(std::to_string(simulation.nb_cor()));
			nb_sca.set_text(std::to_string(simulation.nb_sca()));
			timer_data.set_text("0");
			on_timeout(true);

			m_Area.queue_draw();
		}
		else if (action == Gtk::FileChooser::Action::SAVE) {
			simulation.sauvegarde(filename);
		}
	}
	delete dialog;
}



static void draw_frame(const Cairo::RefPtr<Cairo::Context>& cr, Frame frame) {
	draw_square(1., dmax-1, dmax/2, dmax/2, GREY);
}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
Frame frame) {
	// déplace l'origine au centre de la fenêtre
	cr->translate(frame.width/2, frame.height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(frame.width/(frame.xMax - frame.xMin), \
	 - frame.height / (frame.yMax - frame.yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}
