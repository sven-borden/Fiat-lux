/*
	Fichier:    main.c
	Auteur:     Alix Nepveux & Sven Borden
	Date :      16 mars 2016
	Version:    0.9
	Description:Point d'entree du projet 
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glui.h>
#include <GL/glut.h>
extern "C"
{
	#include "constantes.h"
	#include "graphic.h"
	#include "modele.h"
	#include "utilitaire.h"
}
namespace
{
	int mainWin;
	int width, height;
	GLfloat ratio, xMin, xMax, yMin, yMax;
	double y_dmax, x_dmax;	
	short actionSelect, entitySelect, mode;
	short counterClick = 0;
	POINT tabPoint[MAX_PT];
	
	char *editLoadContent = (char*) "file.txt";
	char *editSaveContent = (char*) "save.txt";
	char buttonStartText[10] = "Start!";
	char buttonStopText[10] = "Stop!";

	bool simulationRunning = false;		

	bool leftButtonDown = false;
	bool rightButtonDown = false;

	float clickX, clickY, relachX, relachY;

	GLUI_EditText * editFileLoad;
	GLUI_EditText * editFileSave;
	
	GLUI_Button * buttonLoad;
	GLUI_Button * buttonSave;

	GLUI_Button * buttonStart;
	GLUI_Button * buttonStep;
	
	GLUI_Button * buttonExit;

	GLUI_EditText * editPhoton;
	GLUI_EditText * editProjecteur;
	GLUI_EditText * editAbsorbeur;
	GLUI_EditText * editReflecteur;
	
	GLUI_RadioGroup * radiogroupAction;
	GLUI_RadioGroup * radiogroupEntity;;
}



#define NB_ARG  	3
#define SUCCESS		1
#define ERROR   	0
#define MODE_ERROR	0
#define MODE_VERIF	1
#define MODE_GRAPH	2
#define MODE_FINAL	3
#define CREATE_WIN	1
#define MAX_CLICK	6

/*GLUI control CallBack*/
#define BUTTON_LOAD_ID 			11
#define BUTTON_SAVE_ID 			12
#define BUTTON_START_ID			13
#define BUTTON_STEP_ID			14
#define BUTTON_EXIT_ID			15
#define EDIT_FILE_LOAD_ID		21
#define EDIT_FILE_SAVE_ID		22
#define EDIT_PHOTON_ID			23
#define EDIT_PROJECTEUR_ID		24
#define EDIT_ABSORBEUR_ID		25
#define EDIT_REFLECTEUR_ID		26
#define RADIOGROUP_ACTION_ID	31
#define RADIOGROUP_ENTITY_ID	32

/*GLUI CONSTANT*/
#define SELECTION_VAL 	0
#define CREATION_VAL	1
#define PROJECTEUR_VAL	0
#define REFLECTEUR_VAL	1
#define ABSORBEUR_VAL	2

/*window*/
#define X_MIN	-DMAX
#define X_MAX	DMAX
#define Y_MIN	-DMAX
#define Y_MAX	DMAX
#define INIT_WIDTH	400
#define INIT_HEIGHT	600
#define GLUI_X 450
#define GLUI_Y 20
#define GLUT_X 20
#define GLUT_Y 20

/*Fonction qui crée le GLUI */
void createGLUI();
/*Fonction callback du GLUI*/
void control_cb(int);
/*Fonction qui appelle la bonne simulation en fonction de l'entrée*/
int call(int, char*);
/*Redessine entierement le contenu du widget GLUT*/
void redrawAll();
/*Widget callback reshape, when resized*/
void reshape_cb(int, int);
/*Widget callback display, when contents have to be redrawn*/
void display_cb(void);
/*Sauvegarde dans un fichier*/
void saveFile(char const*);
/*Charge un fichier*/
void loadFile(char const*);
/*IDLE*/
void idle(void);
/*Button start appuyé*/
void startPressed(void);
/*Button Step appuyé*/
void stepPressed(void);
/*Quitte le programme*/
void exitPressed(void);
/*RadioGroups changé*/
void actionPressed(int);
void entityPressed(int);
/*GLUI mis à jour*/
void updateGLUI(void);
/*Gère les clicks de souris*/
void mouseClick(int , int, int, int);
/*Gère les mouvements de souris*/
void motionClick(int, int);
/*Gère le clavier*/
void keyNormalClick(unsigned char, int, int);
/*Gère les touches autres du clavier*/
void keySpecialClick(int, int, int);
/*Faire le zoom*/
void zoomIn(double, double, double, double);
/*Initialise pour graphic*/
void initGraph(void);
/*Initialise pour Final*/
void initFinal(void);
/*Annule la création*/
void cancelCreation(void);


int main(int argc, char *argv[])
{
	actionSelect = SELECTION_VAL;
	entitySelect = PROJECTEUR_VAL;

	int success = ERROR;
	mode = MODE_ERROR;
	if(argc == NB_ARG)
	{
		editLoadContent = argv[2];
		if(strcmp(argv[1], "Error") == 0)
			mode = MODE_ERROR;
		if(strcmp(argv[1], "Verification") == 0)
			mode = MODE_VERIF;
		if(strcmp(argv[1], "Graphic") == 0)
			mode = MODE_GRAPH;
		if(strcmp(argv[1], "Final") == 0)
			mode = MODE_FINAL;
		success = call(mode, argv[2]);
	}
	else
	{
		mode = MODE_FINAL;
	}
	glutInit(&argc, argv);
	switch(mode)
	{
		case MODE_ERROR:
			if(success)
			{
				modeleSuccess();
				return EXIT_SUCCESS;
			}
			else
				return EXIT_FAILURE;
			break;
		case MODE_VERIF:
			if(success)
				return EXIT_SUCCESS;
			else
				return EXIT_FAILURE;
			break;
		case MODE_GRAPH:
			if(!success)	modeleDestroy();
			initGraph();
			break;
		case MODE_FINAL:
			if(!success)	modeleDestroy();;
			initFinal();
			break;
	}
	return EXIT_SUCCESS;
}

void initFinal(void)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(INIT_WIDTH, INIT_HEIGHT);
	glutInitWindowPosition(GLUT_X, GLUT_Y);
	ratio = (GLfloat)INIT_WIDTH / (GLfloat)INIT_HEIGHT;
	mainWin = glutCreateWindow("Project");
	glClearColor(1.,1.,1.,0.);
	
	glutIdleFunc(idle);
	glutDisplayFunc(display_cb);//si la fenetre bouge
	glutReshapeFunc(reshape_cb);//si la taille change
	glutMouseFunc(mouseClick);
	glutMotionFunc(motionClick);	
	glutKeyboardFunc(keyNormalClick);	
	createGLUI();
	width = INIT_WIDTH; height = INIT_HEIGHT;
	xMin = X_MIN; xMax = X_MAX; yMin = Y_MIN; yMax = Y_MAX;
	x_dmax = y_dmax = DMAX;
	reshape_cb(width, height);
	modeleDraw();
	glutMainLoop();
}

void initGraph(void)
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(INIT_WIDTH, INIT_HEIGHT);
	glutInitWindowPosition(GLUT_X, GLUT_Y);
	ratio = (GLfloat)INIT_WIDTH / (GLfloat)INIT_HEIGHT;
	mainWin = glutCreateWindow("Project");
	glClearColor(1.,1.,1.,0.);
	
	glutIdleFunc(idle);
	glutDisplayFunc(display_cb);//si la fenetre bouge
	glutReshapeFunc(reshape_cb);//si la taille change
	glutMouseFunc(mouseClick);
	glutMotionFunc(motionClick);	
	glutKeyboardFunc(keyNormalClick);	
	glutSpecialFunc(keySpecialClick);
	createGLUI();
	width = INIT_WIDTH; height = INIT_HEIGHT;
	xMin = X_MIN; xMax = X_MAX; yMin = Y_MIN; yMax = Y_MAX;
	x_dmax = y_dmax = DMAX;
	reshape_cb(width, height);
	modeleDraw();
	glutMainLoop();
}

void idle(void)
{
	if(glutGetWindow() != mainWin)
		glutSetWindow(mainWin);

	if(simulationRunning == true)
	{
		modeleUpdate();
	}	
	glutPostRedisplay();
}

void redrawAll(void)
{
	/*Efface le contenu de la win*/
	glClear(GL_COLOR_BUFFER_BIT);
	/*Defini le domaine*/
	glLoadIdentity();

	glOrtho(xMin, xMax, yMin, yMax, -1., 1.);
	modeleDraw();
	if(leftButtonDown == true)
		graphicDrawZoom(clickX,relachX,clickY,relachY);
	if(counterClick > 1 && entitySelect == ABSORBEUR_VAL &&
		actionSelect == CREATION_VAL)
		graphicDrawAbsorbeur(counterClick, tabPoint, 0);	
	glutSwapBuffers();
}

void reshape_cb(int x, int y)
{
	double add;
	glViewport(0, 0, x, y);
	width = x;
	if(y == 0)
		height = 1;
	else
		height = y;
	double aspect_ratio = (double)width/height;
	if(aspect_ratio <= x_dmax/y_dmax)
	{
		add = ((xMax - xMin) / 2 - x_dmax);
		xMin += add;
		xMax -= add;
		add = x_dmax / aspect_ratio - (yMax - yMin) / 2;
		yMin -= add;
		yMax += add;
	}
	else
	{
		add = ((yMax-yMin) / 2 - y_dmax);
		xMin += add;
		xMax -= add;
		add = y_dmax * aspect_ratio - (xMax - xMin) / 2;
		xMin -= add;
		xMax += add;
	}
	ratio = aspect_ratio;
	glutPostRedisplay();
}

void display_cb() 
{
	redrawAll(); 
	updateGLUI();
}

void keyNormalClick(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'r'://reset zoom
			xMin = X_MIN;	yMin = Y_MIN;
			xMax = X_MAX;	yMax = Y_MAX;
			x_dmax = y_dmax = DMAX;
			reshape_cb(width, height);
			break;
		case 'd':
			modeleDestroyEntity(entitySelect);
			break;
		case 'k':
			modeleDestroyExtPhot(xMin, xMax, yMin, yMax);
			break;
		case 's':
			stepPressed();
			break;
		case 32://espace
			startPressed();
			break;
		case 27:
			exitPressed();
			break;
	}
}

void keySpecialClick(int k, int x, int y)
{
	switch(k)
	{
		case GLUT_KEY_UP:
			yMin += y_dmax/10;
			yMax += y_dmax/10;
			break;
		case GLUT_KEY_DOWN:
			yMin -= y_dmax/10;
			yMax -= y_dmax/10;
			break;
		case GLUT_KEY_RIGHT:
			xMin += x_dmax/10;
			xMax += x_dmax/10;
			break;
		case GLUT_KEY_LEFT:
			xMin -= x_dmax/10;
			xMax -= x_dmax/10;
			break;
	}
	glutPostRedisplay();
	return;
}

void zoomIn(double x1, double y1, double x2, double y2)
{
	glLoadIdentity();

	/*swap pour que x1 < x2 et y1 < y2*/
	if(x1 > x2)
		utilitaireSwap(&x1, &x2);
	if(y1 > y2)
		utilitaireSwap(&y1, &y2);

	double _w = fabs(x1 - x2);
	double _h = fabs(y1 - y2);
	x_dmax = _w / 2;	y_dmax = _h / 2;
	double diag = sqrt((_w*_w) + (_h*_h));
	if(diag <= EPSIL_CREATION)
		return;	
	
	GLfloat _ratio = (GLfloat) _w / (GLfloat) _h;
	if(ratio < _ratio)
		_h = _w/ratio;
	if(ratio > _ratio)
		_w = ratio*_h;

	double diff = _w - fabs(x1 - x2);

	if(diff > 0)
	{
		x1 -= diff/2;
		x2 += diff/2;
	}

	diff = _h - fabs(y1 - y2);

	if(diff > 0)
	{
		y1 -= diff/2;
		y2 += diff/2;
	}

	/*on peut mtn recadrer*/
	xMin = x1; xMax = x2; 
	yMin = y1; yMax = y2;	
}

int call(int mode, char* fileName)
{
	int success = SUCCESS;	
	switch(mode)
	{
		case MODE_ERROR:
			success = modeleLecture(fileName);
			
			break;
		case MODE_VERIF:
			success = modeleLecture(fileName);
			if(success != SUCCESS)
				break;
			success = modele_verification_rendu2();
			break;
		case MODE_GRAPH:
		case MODE_FINAL:
			success = modeleLecture(fileName);
			if(success != SUCCESS)
				break;
			success = modele_verification_rendu2();
			break;
		default:
			success = ERROR;
	}
	return success;
}

void mouseClick(int button, int state, int x, int y)
{
	double _x, _y;
	_x = ((double)x/width)*(xMax - xMin) + xMin;
	_y = ((double)(height - y)/height)*(yMax - yMin) + yMin;
	
	if(button == GLUT_LEFT_BUTTON)
	{
		/* vérifie que seul un bouton est pressé*/
		if(rightButtonDown == true)
			return;
		if(state == GLUT_DOWN)
		{
			if(leftButtonDown == false)
			{
				leftButtonDown = true;
				clickX = _x; clickY = _y;
				relachX = clickX; relachY = clickY;
			}
		}
		else
		{
			if(leftButtonDown == true)//button relaché
			{
				leftButtonDown = false;
				relachX = _x; relachY = _y;		
				VECTOR diagonale;
				diagonale.ptDeb.x = clickX;
				diagonale.ptDeb.y = clickY;
				diagonale.ptFin.x = relachX;
				diagonale.ptDeb.y = relachY;
				if(utilitaireNormeVector(diagonale) > EPSIL_CREATION)
					zoomIn(clickX, clickY, relachX, relachY);
			}
		}
	}
	if(button == GLUT_RIGHT_BUTTON)
	{
		if(simulationRunning)
			return;
		if(state == GLUT_DOWN)
		{
			rightButtonDown = true;
			if(actionSelect == SELECTION_VAL)
				modeleSelect(entitySelect, _x, _y);
		}
		if(state == GLUT_UP)
			if(rightButtonDown == true)
			{
				tabPoint[counterClick].x = _x;
				tabPoint[counterClick].y = _y;
				counterClick++;
				if(actionSelect ==	CREATION_VAL)
					if(entitySelect != ABSORBEUR_VAL)
						if(counterClick == 2)
						{
							modeleCreation(entitySelect, counterClick, 
								tabPoint);
							counterClick = 0;
						}	
				if(counterClick == MAX_CLICK)
				{
					modeleCreation(entitySelect, counterClick, tabPoint);
					counterClick = 0;
				}
				rightButtonDown = false;
			}
	}
}

void motionClick(int x, int y)
{
	double _x, _y;
	_x = ((double)x/width)*(xMax - xMin) + xMin;
	_y = ((double)(height - y)/height)*(yMax - yMin) + yMin;
	
	if(leftButtonDown)
		relachX = _x; relachY = _y;
	if(rightButtonDown && actionSelect == SELECTION_VAL)
	{
		modeleSelect(entitySelect, _x, _y);
	}
}

void updateGLUI()
{
	
	editPhoton->set_int_val(modeleNbPhot());
	editReflecteur->set_int_val(modeleNbRefl());
	editAbsorbeur->set_int_val(modeleNbAbso());
	editProjecteur->set_int_val(modeleNbProj());
}

void createGLUI()
{
	GLUI *glui = GLUI_Master.create_glui((char *) "Fiat-lux", 0, GLUI_X, GLUI_Y);
	//PANEL FILE
	GLUI_Panel * panelFile = glui->add_panel((char*)"FILE",
		GLUI_PANEL_EMBOSSED);
	editFileLoad = glui->add_edittext_to_panel(panelFile,
		(char*)"File Name:", GLUI_EDITTEXT_TEXT, editFileLoad,
		EDIT_FILE_LOAD_ID, control_cb);
	buttonLoad = glui->add_button_to_panel(panelFile, 
		(char*) "Load", BUTTON_LOAD_ID, control_cb);
	editFileSave = glui->add_edittext_to_panel(panelFile,
		(char*)"Save File:", GLUI_EDITTEXT_TEXT, editFileSave,
		EDIT_FILE_SAVE_ID, control_cb);
	buttonSave = glui->add_button_to_panel(panelFile,
		(char*) "Save", BUTTON_SAVE_ID, control_cb);
	//PANEL SIMULATION
	GLUI_Panel * panelSimulation = glui->add_panel((char*)"Simulation",
		GLUI_PANEL_EMBOSSED);
	buttonStart = glui->add_button_to_panel(panelSimulation,
		(char*) "Start!", BUTTON_START_ID, control_cb);
	buttonStep = glui->add_button_to_panel(panelSimulation,
		(char*) "Step", BUTTON_STEP_ID, control_cb);
	buttonExit = glui->add_button(
		(char*) "exit", BUTTON_EXIT_ID, control_cb);
	//COLUMN
	glui->add_column(1);	
	//PANEL INFORMATION
	GLUI_Panel *panelInformation = glui->add_panel((char*) "Information",
		GLUI_PANEL_EMBOSSED);
	editPhoton = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Photons", GLUI_EDITTEXT_INT, 0,
		EDIT_PHOTON_ID, control_cb);
	editProjecteur = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Projecteurs", GLUI_EDITTEXT_INT, 0,
		EDIT_PROJECTEUR_ID, control_cb);
	editAbsorbeur = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Absorbeurs", GLUI_EDITTEXT_INT, 0,
		EDIT_ABSORBEUR_ID, control_cb);
	editReflecteur = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Reflecteurs", GLUI_EDITTEXT_INT, 0,
		EDIT_REFLECTEUR_ID, control_cb);
	//PANEL MOUSE
	GLUI_Panel *panelMouse = glui->add_panel((char*)"Mouse panel",
		GLUI_PANEL_EMBOSSED);
	GLUI_Panel *panelAction = glui->add_panel_to_panel(panelMouse,
		(char*)"Action selection", GLUI_PANEL_EMBOSSED);
	GLUI_Panel *panelEntity = glui->add_panel_to_panel(panelMouse,
		(char*)"Entity selection", GLUI_PANEL_EMBOSSED);
	radiogroupAction = glui->add_radiogroup_to_panel(panelAction,
		NULL, RADIOGROUP_ACTION_ID, control_cb);
	glui->add_radiobutton_to_group(radiogroupAction, 
		(char*) "Selection");
	glui->add_radiobutton_to_group(radiogroupAction, 
		(char*) "Creation");
	radiogroupEntity = glui->add_radiogroup_to_panel(panelEntity,
		NULL, RADIOGROUP_ENTITY_ID, control_cb);
	glui->add_radiobutton_to_group(radiogroupEntity, 
		(char*) "Projecteur");
	glui->add_radiobutton_to_group(radiogroupEntity,
		(char*) "Reflecteur");
	glui->add_radiobutton_to_group(radiogroupEntity,
		(char*) "Absorbeur");
	editFileLoad->set_text(editLoadContent);
	editFileSave->set_text(editSaveContent);
	glui->set_main_gfx_window(mainWin);
}

void control_cb(int control)
{
	switch(control)
	{
		case (BUTTON_LOAD_ID):
			loadFile(editFileLoad->get_text());
			break;
		case (BUTTON_SAVE_ID):
			saveFile(editFileSave->get_text());
			break;
		case (BUTTON_START_ID):
			startPressed();
			break;		
		case (BUTTON_STEP_ID):
			stepPressed();
			break;
		case (BUTTON_EXIT_ID):
			exitPressed();
			break;
		case (EDIT_FILE_LOAD_ID):
			break;
		case (EDIT_FILE_SAVE_ID):
			break;
		case (EDIT_PHOTON_ID):
			break;
		case (EDIT_PROJECTEUR_ID):
			break;
		case (EDIT_ABSORBEUR_ID):
			break;
		case (EDIT_REFLECTEUR_ID):
			break;
		case (RADIOGROUP_ACTION_ID):
			actionPressed(radiogroupAction->get_int_val());
			break;
		case (RADIOGROUP_ENTITY_ID):
			entityPressed(radiogroupEntity->get_int_val());
			break;
		default:
			break;
	}
}

void saveFile(char const *name)
{
	modeleWrite((char*) name);
}

void loadFile(char const *name)
{
	modeleDestroy();
	if(call(MODE_VERIF, (char*) name))
	{
		if(ratio <= 1.)
		{
			xMin = X_MIN;	xMax = X_MAX;
			yMin = Y_MIN / ratio;
			yMax = Y_MAX / ratio;
		}
		else
		{
			xMin = X_MIN * ratio;
			xMax = X_MAX * ratio;
			yMin = Y_MIN;	yMax = Y_MAX;
		}
		glutPostRedisplay();
		redrawAll();;//refresh;
	}
}

void startPressed(void) 
{
	if(simulationRunning == false)
		buttonStart->set_name(buttonStopText);
	else
		buttonStart->set_name(buttonStartText);
	simulationRunning = !simulationRunning;
}

void stepPressed(void) { modeleUpdate();}

void exitPressed(void) { exit(1); }

void actionPressed(int val)
{	
	if(actionSelect != val)
	{
		if(counterClick > 1 && entitySelect == ABSORBEUR_VAL)
			modeleCreation(entitySelect, counterClick, tabPoint);
		modeleUnselect();
		cancelCreation();
	}
	actionSelect = val;

	if(mode == MODE_GRAPH)
		switch(val)
		{
			case SELECTION_VAL:
				printf("Selection selected\n");
			
				break;
			case CREATION_VAL:
				printf("Creation selected\n");
				break;
		}
}

void entityPressed(int val)
{
	if(entitySelect != val)
	{
		if(counterClick > 1 && entitySelect == ABSORBEUR_VAL)
			modeleCreation(entitySelect, counterClick, tabPoint);
		modeleUnselect();
		cancelCreation();
	}
	entitySelect = val;
	if(mode == MODE_GRAPH)
		switch(val)
		{
			case PROJECTEUR_VAL:
				printf("Selected Projecteur\n");
				break;
			case REFLECTEUR_VAL:
				printf("Selected Reflecteur\n");
				break;
			case ABSORBEUR_VAL:
				printf("Selected Absorbeur\n");
				break;
		}
}

void cancelCreation(void)
{
	counterClick = 0;
}
