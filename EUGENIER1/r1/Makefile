#Makefile for generating rendu1.x
# Definitions de macros

CC     = gcc
CFLAGS = -Wall
CFILES = absorbeur.c error.c main.c modele.c photon.c projecteur.c reflecteur.c utilitaire.c
OFILES = absorbeur.o error.o main.o modele.o photon.o projecteur.o reflecteur.o utilitaire.o

# Definition de la premiere regle

rendu1.x: $(OFILES)
	$(CC) $(OFILES) -lm -o rendu1.x

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
absorbeur.o: absorbeur.c constantes.h tolerance.h error.h absorbeur.h \
 utilitaire.h
error.o: error.c error.h
main.o: main.c modele.h
modele.o: modele.c absorbeur.h constantes.h tolerance.h error.h modele.h \
 photon.h projecteur.h reflecteur.h utilitaire.h
photon.o: photon.c constantes.h tolerance.h error.h photon.h utilitaire.h
projecteur.o: projecteur.c constantes.h tolerance.h error.h projecteur.h \
 utilitaire.h
reflecteur.o: reflecteur.c constantes.h tolerance.h error.h reflecteur.h \
 utilitaire.h
utilitaire.o: utilitaire.c utilitaire.h
