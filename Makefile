# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++17
CXXFILES = projet.cc shape.cc lifeform.cc simulation.cc message.cc
OFILES = $(CXXFILES:.cc=.o)

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
projet.o: projet.cc simulation.h shape.h lifeform.h
shape.o: shape.cc shape.h
lifeform.o: lifeform.cc shape.h constantes.h message.h lifeform.h
simulation.o: simulation.cc message.h simulation.h shape.h lifeform.h
message.o: message.cc message.h
