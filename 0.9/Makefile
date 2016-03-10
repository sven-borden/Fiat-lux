# Makefile
# Authors   : Alix Nepveux & Sven Borden
# Date      : 25.02.2016
# Version   : 0.9 (BETA)

# Description
## This file does what it should do.

###VARIABLES###
CC = gcc

CFLAGS = -Wall -ansi

CFILES = absorbor.c photon.c reflector.c model.c tools.c error.c emmit.c emmit.h

OFILES = $(CFILES:.c=.o)

###DEPENDENCIES###

all: projet.x

absorbor.o  : absorbor.c absorbor.h error.h tools.h
    $(CC) $(CFLAGS) -c $< -o $@

photon.o    : photon.c photon.h error.h tools.h
    $(CC) $(CFLAGS) -c $< -o $@

reflector.o : reflector.c reflector.h error.h tools.h
    $(CC) $(CFLAGS) -c $< -o $@

emmit.o     : emmit.c emmit.h error.h tools.h
    $(CC) $(CFLAGS) -c $< -o $@
    
error.o     : error.c error.h
    $(CC) $(CFLAGS) -c $< -o $@

model.o: model.c model.h absorbor.h photon.h reflector.h emmit.h

projet.x    : $(OFILES)
    $(CC) $(OFILES) -o $@
    
clean       :
    @echo "***cleaning all objects and executables***"
    @/bin/rm -f *.o *.x *.c~ *.h~