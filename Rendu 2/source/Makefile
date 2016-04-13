#Makefile for generating rendu1.x

#Definitions

CC      = gcc
CFLAGS  = -Wall
CFILES  = main.cpp absorbeur.c error.c graphic.c lecture.c modele.c photon.c projecteur.c reflecteur.c utilitaire.c

OFILES = $(CFILES:.c=.o) 

rendu2.x: $(OFILES)
	$(CC) $(OFILES) -lm -lstdc++ -lglut -Llib -lglui -lGL -o rendu2.x
    
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
main.o: main.cpp modele.h constantes.h tolerance.h graphic.c graphic.h \
 utilitaire.h
absorbeur.o: absorbeur.c constantes.h tolerance.h error.h utilitaire.h \
 absorbeur.h
error.o: error.c error.h
graphic.o: graphic.c constantes.h tolerance.h graphic.h utilitaire.h
lecture.o: lecture.c absorbeur.h utilitaire.h constantes.h tolerance.h \
 error.h reflecteur.h photon.h projecteur.h lecture.h
modele.o: modele.c absorbeur.h utilitaire.h constantes.h tolerance.h \
 error.h lecture.h reflecteur.h photon.h projecteur.h modele.h
photon.o: photon.c constantes.h tolerance.h error.h utilitaire.h photon.h
projecteur.o: projecteur.c constantes.h tolerance.h error.h utilitaire.h \
 projecteur.h
reflecteur.o: reflecteur.c constantes.h tolerance.h error.h utilitaire.h \
 reflecteur.h
utilitaire.o: utilitaire.c utilitaire.h
