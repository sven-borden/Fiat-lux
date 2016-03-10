#ifndef MODEL_H
#define MODEL_H

void startSimulation();//demarre la simulation
void pauseSimulation();//met la simulation en pause
void killPhoton();//tue les photos hors cadrage
void deleteSelection();
void leftClick(double x1, double y1, double x2, double y2);
void rightClick(double x1, double y1, double x2, double y2);//besoin encore en interne d'une fonction de selection

#endif