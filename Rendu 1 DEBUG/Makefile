#Makefile for generating rendu1.x

#Definitions

CC      = gcc
CFLAGS  = -Wall
CFILES  = main.c absorbeur.c error.c modele.c photon.c projecteur.c reflecteur.c utilitaire.c

OFILES = $(CFILES:.c=.o) 

rendu1.x: $(OFILES)
	$(CC) $(OFILES) -lm -o rendu1.x
    
depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
        	$(CC) -MM $(CFLAGS) $(CFILES) | \
        	egrep -v "/usr/include" \
        	) > Makefile.new
	@mv Makefile.new Makefile
    
clean:
	@echo " *** MODULES OBJETS ET EXECUTABLES EFFACE ***"
	@/bin/rm -f *.o *.x *.c~ *.h~
    
###Règles automatiques
#
#
# DO NOT DELETE THIS LINE
main.o: main.c modele.h
absorbeur.o: absorbeur.c error.h absorbeur.h utilitaire.h constantes.h \
 tolerance.h
error.o: error.c error.h
modele.o: modele.c absorbeur.h utilitaire.h reflecteur.h photon.h \
 constantes.h tolerance.h projecteur.h error.h
photon.o: photon.c utilitaire.h constantes.h tolerance.h photon.h
projecteur.o: projecteur.c error.h absorbeur.h utilitaire.h constantes.h \
 tolerance.h
reflecteur.o: reflecteur.c utilitaire.h constantes.h tolerance.h \
 reflecteur.h
utilitaire.o: utilitaire.c
