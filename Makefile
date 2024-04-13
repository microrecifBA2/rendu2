# Definitions de macros

OUT = projet
CXX  = g++
CXXFLAGS = -g -Wall -std=c++17
OFILES = projet.o shape.o lifeform.o simulation.o message.o gui.o
LINKING = `pkg-config --cflags gtkmm-4.0`
LDLIBS = `pkg-config --libs gtkmm-4.0`

all: $(OUT)

shape.o: shape.cc shape.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

lifeform.o: lifeform.cc shape.h constantes.h message.h lifeform.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

simulation.o: simulation.cc message.h simulation.h shape.h lifeform.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

message.o: message.cc message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

gui.o: gui.cc gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

projet.o: projet.cc gui.h simulation.h shape.h lifeform.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)


clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

