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
	char editLoadContent[100] = "file.txt";
	char editSaveContent[100] = "save.txt";
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
}

#define NB_ARG  3
#define ERROR   1

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

void createGLUI();
void control_cb(int);


int main(int argc, char *argv[])
{
	if(argc == NB_ARG)
	{
		if(strcmp(argv[1], "Error") == 0)
		{
			if(modeleLecture(argv[2]) == ERROR)
				EXIT_FAILURE;
			else
				EXIT_SUCCESS;
		}
		if(strcmp(argv[1], "Verification") == 0)
		{
			if(modeleLecture(argv[2]) == ERROR)
				EXIT_FAILURE;
			else
				EXIT_SUCCESS;
		}
		if(strcmp(argv[1], "Graphic") == 0)
		{
			;
		}
	}
	glutInit(&argc, argv);
	createGLUI();
	glutMainLoop();
	return 0;
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
		(char*) "Nb Photons", GLUI_EDITTEXT_TEXT, (char*)"CONTENU",
		EDIT_PHOTON_ID, control_cb);

	editProjecteur = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Projecteurs", GLUI_EDITTEXT_TEXT, (char*)"CONTENU",
		EDIT_PROJECTEUR_ID, control_cb);
	
	editAbsorbeur = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Absorbeurs", GLUI_EDITTEXT_TEXT, (char*)"CONTENU",
		EDIT_ABSORBEUR_ID, control_cb);
	
	editReflecteur = glui->add_edittext_to_panel(panelInformation,
		(char*) "Nb Reflecteurs", GLUI_EDITTEXT_TEXT, (char*)"CONTENU",
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
}

void control_cb(int control)
{
	switch(control)
	{
		case (BUTTON_LOAD_ID):
			break;
		case (BUTTON_SAVE_ID):
			break;
		case (BUTTON_START_ID):
			break;
		case (BUTTON_STEP_ID):
			break;
		case (BUTTON_EXIT_ID):
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
			break;
		case (RADIOGROUP_ENTITY_ID):
			break;
		default:
			break;
	}
}
