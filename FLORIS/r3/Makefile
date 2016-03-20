# Definitions de macros

CC     = gcc
CFLAGS = -Wall
CFILES = main.c modele.c projecteur.c error.c reflecteur.c absorbeur.c photon.c
OFILES = main.o modele.o projecteur.o error.o reflecteur.o absorbeur.o photon.o

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
calendrier.o: calendrier.c calendrier.h
difference.o: difference.c calendrier.h difference.h
main.o: main.c calendrier.h difference.h
