# Definitions de macros

CC     = gcc
CFLAGS = -g
LIBS   = -lglut -lGL -lGLU -lm -lglui -L/usr/X11R6/lib -lX11 -lXext \
 -lXmu -lXi -lstdc++
CFILES = absorbeur.c photon.c projecteur.c reflecteur.c error.c main.cpp \
 modele.c utilitaire.c graphic.c
OFILES = $(CFILES:.c=.o)

# Definition de la premiere regle

rendu2.x: $(OFILES)
	$(CC) $(OFILES) -lm -o rendu2.x ${LIBS}

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.c~ *.h~

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
absorbeur.o: absorbeur.c constantes.h tolerance.h utilitaire.h error.h \
 absorbeur.h graphic.h
photon.o: photon.c photon.h error.h utilitaire.h constantes.h tolerance.h \
 graphic.h
projecteur.o: projecteur.c utilitaire.h projecteur.h error.h constantes.h \
 tolerance.h graphic.h
reflecteur.o: reflecteur.c utilitaire.h reflecteur.h error.h constantes.h \
 tolerance.h graphic.h
error.o: error.c error.h
main.o: main.cpp modele.h constantes.h tolerance.h
modele.o: modele.c utilitaire.h modele.h constantes.h tolerance.h \
 absorbeur.h reflecteur.h projecteur.h photon.h error.h graphic.h
utilitaire.o: utilitaire.c constantes.h tolerance.h utilitaire.h
graphic.o: graphic.c graphic.h
