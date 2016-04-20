/*
	Fichier:    main.c
	Auteur:     Alix Nepveux & Sven Borden
	Date :      16 mars 2016
	Version:    0.9
	Description:Point d'entree du projet 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glui.h>
#include <GL/glut.h>

namespace
{
	int mainWin;
	int width, height;
	char editLoadContent[100] = "file.txt";
	char editSaveContent[100] = "save.txt";
	char buttonStartText[10] = "Start!";
	char buttonStopText[10] = "Stop!";
	bool simulationRunning = false;		
	static GLfloat ratio;
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

extern "C"
{
	#include "modele.h"
	#include "graphic.h"
	#include "constantes.h"
}

#define NB_ARG  	3
#define SUCCESS		0
#define ERROR   	1
#define MODE_ERROR	0
#define MODE_VERIF	1
#define MODE_GRAPH	2
#define CREATE_WIN	1

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

/*Fonction qui crée le GLUI */
void createGLUI();
/*fonction callback du GLUI*/
void control_cb(int);
/*Fonction qui appelle la bonne simulation en fonction de l'entrée*/
int call(int, char[]);
/*Redessine entierement le contenu du widget GLUT*/
void redrawAll();
/*Widget callback reshape, when resized*/
void reshape_cb(int, int);
/*Widget callback display, when contents have to be redrawn*/
void display_cb();
void saveFile(char const*);
void loadFile(char const*);
void idle(void);
void startPressed(void);
void stepPressed(void);
void exitPressed(void);
void actionPressed(int);
void entityPressed(int);
void updateGLUI(void);
int main(int argc, char *argv[])
{
	int success = ERROR;
	int mode = MODE_ERROR;
	if(argc == NB_ARG)
	{
		if(strcmp(argv[1], "Error") == 0)
			mode = MODE_ERROR;
		if(strcmp(argv[1], "Verification") == 0)
			mode = MODE_VERIF;
		if(strcmp(argv[1], "Graphic") == 0)
			mode = MODE_GRAPH;
		
		success = call(mode, argv[2]);
	}
	else
	{
		mode = MODE_GRAPH;
	}
	if(mode == MODE_ERROR)
		if(success)
			return EXIT_SUCCESS;
		else
			return EXIT_FAILURE;
	if(mode == MODE_VERIF)
		if(success)
			return EXIT_SUCCESS;
		else
			return EXIT_FAILURE;
	if(mode == MODE_GRAPH)
	{
		if(!success)
			modeleDestroy();
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(800, 1000);
		ratio = (GLfloat)800 / (GLfloat)1000;
		mainWin = glutCreateWindow("Project");
		glClearColor(1.,1.,1.,0.);
		glutIdleFunc(idle);
		glutDisplayFunc(display_cb);//si la fenetre bouge
		glutReshapeFunc(reshape_cb);//si la taille change
		createGLUI();
		modeleDraw();
		glutMainLoop();
	}
	return EXIT_SUCCESS;
}

void idle(void)
{
	if(glutGetWindow() != mainWin)
		glutSetWindow(mainWin);

	glutPostRedisplay();
}

void redrawAll(void)
{
	/*Efface le contenu de la win*/
	glClear(GL_COLOR_BUFFER_BIT);
	/*Defini le domaine*/
	glLoadIdentity();
	if(ratio <= 1.)
		glOrtho(-1., 1., -1./ratio, 1./ratio, -1., 1.);
	else
		glOrtho(-1./ratio, 1./ratio, -1., 1., -1., 1.);

	modeleUpdate();
	glutSwapBuffers();
}

void reshape_cb(int x, int y)
{
	width = x;
	height = y;

	glViewport (0, 0, width, height);
		
	ratio = (GLfloat)x / (GLfloat) y;

	glutPostRedisplay();
}

void display_cb() 
{
	redrawAll(); 
	updateGLUI();
}

int call(int mode, char fileName[])
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

void updateGLUI()
{
	editPhoton->set_int_val(modeleNbPhot());
	editReflecteur->set_int_val(modeleNbRefl());
	editAbsorbeur->set_int_val(modeleNbAbso());
	editProjecteur->set_int_val(modeleNbProj());
}

void createGLUI()
{
	GLUI *glui = GLUI_Master.create_glui((char *) "Projet PROG");
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
	if(call(MODE_VERIF, (char*) name))
		redrawAll();;//refresh;
}

void startPressed(void) 
{
	if(simulationRunning == false)
	{
		buttonStart->set_text(buttonStopText);
		printf("Start simulation\n"); 
	}
	else
	{
		buttonStart->set_text(buttonStartText);
		printf("Stop simulation\n");
	}
	simulationRunning = !simulationRunning;
}

void stepPressed(void) { printf("Step by one\n"); }

void exitPressed(void) { exit(1); }

void actionPressed(int val)
{
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
