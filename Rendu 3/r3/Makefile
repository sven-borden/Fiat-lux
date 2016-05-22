#Makefile for generating rendu1.x

#Definitions

CC      = gcc
CFLAGS  = -Wall
CFILES  = ../source/main.cpp ../source/absorbeur.c ../source/error.c ../source/graphic.c ../source/lecture.c ../source/modele.c ../source/photon.c ../source/projecteur.c ../source/reflecteur.c ../source/utilitaire.c
OFILES = $(CFILES:.c=.o) 

rendu3.x: $(OFILES)
	$(CC) $(OFILES) -lm -lglut -lGL -lGLU -Llib -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXi -lstdc++ -lglui -o rendu3.x
    
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
main.o: main.cpp constantes.h tolerance.h graphic.h utilitaire.h modele.h
absorbeur.o: absorbeur.c constantes.h tolerance.h error.h graphic.h \
 utilitaire.h absorbeur.h
error.o: error.c error.h
graphic.o: graphic.c constantes.h tolerance.h utilitaire.h graphic.h
lecture.o: lecture.c absorbeur.h utilitaire.h constantes.h tolerance.h \
 error.h reflecteur.h photon.h projecteur.h lecture.h
modele.o: modele.c absorbeur.h utilitaire.h constantes.h tolerance.h \
 error.h lecture.h reflecteur.h photon.h projecteur.h modele.h
photon.o: photon.c absorbeur.h utilitaire.h constantes.h tolerance.h \
 error.h graphic.h reflecteur.h photon.h
projecteur.o: projecteur.c absorbeur.h utilitaire.h constantes.h \
 tolerance.h error.h graphic.h projecteur.h
reflecteur.o: reflecteur.c absorbeur.h utilitaire.h constantes.h \
 tolerance.h error.h graphic.h projecteur.h reflecteur.h
utilitaire.o: utilitaire.c constantes.h tolerance.h utilitaire.h
