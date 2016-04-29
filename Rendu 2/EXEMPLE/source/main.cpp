/*!
 \file main.cpp
 \brief calls the principal actions demanded
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.2
 \date 21 april 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

extern "C"
{
	#include "modele.h"
}

#define LOAD_ID  11
#define SAVE_ID  12
#define START_ID 13
#define STEP_ID  14
#define ACTION_ID 31
#define ENTITY_ID 32
#define WINDOWS_X 400
#define WINDOWS_Y 500
#define GLUI_POS_X 20
#define GLUI_POS_Y 20
#define GLUT_POS_Y 20
#define GLUT_POS_X 440

// main-window
void glut_window(void);
// control-window
void glui_window(char *text);
// idle: standard actions
void idle_cb(void);
//callback for buttons
void control_cb(int control);
//callback for reshaping-event
void reshape_cb(int x, int y);
//callback when the picture has to be "rebuilt/built"
void display_cb(void);
//callbacks for keyboard-events
void keyboard_cb(unsigned char key, int x, int y);  //normal keys
void specialkeys_cb(int k, int x, int y);   //special keys
//callbacks for mouse events
void mouse_click_cb(int button, int button_state, int x, int y);
void mouse_motion_cb(int x, int y);
//conversion from "mouse-coordinates" to the coordinates of the "world"
void click_position(int x, int y, double *xpos, double *ypos);
//zooms, with necessary changes for a reshape-event
void zoom(void);
//asks the modules for the number of existing elements
void statistic_update(void);

namespace
{
	GLUI_Button 	*bstart 	   = NULL;
	GLUI_EditText 	*filename_save = NULL;
	GLUI_EditText 	*filename_load = NULL;
	GLUI_StaticText *nb_photon 	   = NULL;
	GLUI_StaticText *nb_projecteur = NULL;
	GLUI_StaticText *nb_absorbeur  = NULL;
	GLUI_StaticText *nb_reflecteur = NULL;
	GLUI_RadioGroup *radio_action  = NULL;
	GLUI_RadioGroup *radio_entity  = NULL;
	GLfloat x_min, x_max, y_min, y_max; //field of view
	int statistic[4] = {0};
	int main_window;
	int width, height;
	bool click;  //if click is ongoing: 1
	double clickstart_x = 0, clickstart_y = 0,
		   clickend_x   = 0, clickend_y   = 0;
	double y_dmax, x_dmax; //minimum part of picture which is always shown
	bool move = false, update = false, selected = false; // For the final:
	int beginnew = 1;
	int live_action, live_entity;
	int element;
}

int main(int argc, char * argv[])
{
	char text[] = "test.txt";

	glutInit(&argc, argv);

	if(argc == MODELE_NUM_ARGU)
	{
		if(!(strcmp("Error", argv[1]) && strcmp("Verification", argv[1])
		     && strcmp("Graphic", argv[1]) && strcmp("Final", argv[1])))
		{
			if(!modele_lecture(argv[2]))
				modele_delete();
			if(strcmp("Error", argv[1])) //if not Error-mode
			{
				if(!modele_verification_rendu2())
					modele_delete();
				if(strcmp("Verification", argv[1])) //if G- or F-mode
				{
					glut_window();
					glui_window(argv[2]);
					if(strcmp("Graphic", argv[1]))
						update = true;
 				}
			}
		}
		else  //if the arguments are invalid
			modele_error_cl();
	}
	else  //calls modele_lecture without file_name
	{
		glut_window();
		glui_window(text);
	}
	if(nb_photon && nb_projecteur && nb_absorbeur && nb_reflecteur)
		GLUI_Master.set_glutIdleFunc(idle_cb);
		glutMainLoop();

	return EXIT_SUCCESS;
}

void glut_window(void) // Creation of the window glut
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOWS_X, WINDOWS_Y);
	glutInitWindowPosition(GLUT_POS_X, GLUT_POS_Y);
	main_window = glutCreateWindow("Fiat Lux !");
	glutDisplayFunc(display_cb);
	glutReshapeFunc(reshape_cb);
	glutMouseFunc(mouse_click_cb);
	glutMotionFunc(mouse_motion_cb);
	glutKeyboardFunc(keyboard_cb);
	glutSpecialFunc(specialkeys_cb);
	width = WINDOWS_X;
	height = WINDOWS_Y;
	keyboard_cb('r', 0, 0);  //set-back & adjustments of coordinate system
}

void glui_window(char *text) // Creation of the window glui
{
	GLUI *glui = GLUI_Master.create_glui((char*) "Fiat Lux !", 0, 
											GLUI_POS_X, GLUI_POS_Y);
	// Creation of the panel "File"
	GLUI_Panel *panel = glui->add_panel("File");
	filename_load = glui->add_edittext_to_panel(panel, "FileName:",
												GLUI_EDITTEXT_TEXT);
	filename_load->set_text(text);
	glui->add_button_to_panel(panel, "Load", LOAD_ID, control_cb);
	filename_save = glui->add_edittext_to_panel(panel, "FileName:",
												GLUI_EDITTEXT_TEXT);
	filename_save->set_text("save.txt");
	glui->add_button_to_panel(panel, "Save", SAVE_ID, control_cb);

	// Creation of the panel "Simulation"
	panel  = glui->add_panel("Simulation");
	bstart = glui->add_button_to_panel(panel, "Start !", START_ID, control_cb);
	glui->add_button_to_panel(panel, "Step", STEP_ID, control_cb);

	// Exit button and beginning of the second column
	glui->add_button("Exit", 0, (GLUI_Update_CB)exit);
	glui->add_column(true);

	// Creation of the panel "Information"
	panel 		  = glui->add_panel("Information");
	nb_photon 	  = glui->add_statictext_to_panel(panel, "Nb Photons:");
	nb_projecteur = glui->add_statictext_to_panel(panel, "Nb Projecteurs:");
	nb_absorbeur  = glui->add_statictext_to_panel(panel, "Nb Absorbeurs:");
	nb_reflecteur = glui->add_statictext_to_panel(panel, "Nb Reflecteurs:");
	glui->add_column_to_panel(panel, false);
	nb_photon 	  = glui->add_statictext_to_panel(panel, (char*) "0");
	nb_absorbeur  = glui->add_statictext_to_panel(panel, (char*) "0");
	nb_reflecteur = glui->add_statictext_to_panel(panel, (char*) "0");
	nb_projecteur = glui->add_statictext_to_panel(panel, (char*) "0");

	// Creation of the panel "Mouse panel"
	GLUI_Panel *outerpanel = glui->add_panel("Mouse panel");

	panel = glui->add_panel_to_panel(outerpanel, "Action selection");
	radio_action = glui->add_radiogroup_to_panel(panel, &live_action,
												 ACTION_ID, control_cb);
	glui->add_radiobutton_to_group(radio_action, "Selection");
	glui->add_radiobutton_to_group(radio_action, "Creation");

	panel =  glui->add_panel_to_panel(outerpanel, "Entity selection");
	radio_entity = glui->add_radiogroup_to_panel(panel, &live_entity,
												 ENTITY_ID, control_cb);
	glui->add_radiobutton_to_group(radio_entity, "Projecteur");
	glui->add_radiobutton_to_group(radio_entity, "Reflecteur");
	glui->add_radiobutton_to_group(radio_entity, "Absorbeur");

	glui->set_main_gfx_window(main_window);
}

void idle_cb(void)
{
	if(move)
	{
		if(update) //For the final rendu
		{
			modele_update();
			glutPostRedisplay();
		}
		else
			printf("update_sim\n");
	}
}

void control_cb(int control)
{
	switch(control)
	{
		case LOAD_ID:
			modele_delete();
			if(!modele_lecture(filename_load->get_text())
			   || !modele_verification_rendu2())
				modele_delete();
			keyboard_cb('r', 0, 0);
			modele_statistic(statistic);
			nb_photon	 ->set_int_val(statistic[PH]);
			nb_projecteur->set_int_val(statistic[PJ]);
			nb_absorbeur ->set_int_val(statistic[AS]);
			nb_reflecteur->set_int_val(statistic[RF]);
			break;
		case SAVE_ID:
			modele_save(filename_save->get_text());
			break;
		case START_ID:  // For the final rendu
			if(!move)
			{
				bstart->set_name("Stop");
				move 	 = true;
				beginnew = true;
				selected = false;
			}
			else
			{
				bstart->set_name("Start!");
				move = false;
			}
			break;
		case STEP_ID: // For the final rendu
			if(!move)
				if(update)
					modele_update();
				else
					printf("step_sim\n");
			break;
		case ACTION_ID:  // For the final rendu
		case  ENTITY_ID:
		    printf("sim selection released\n");
			beginnew = true;
			selected = false;
			break;
		default:
			printf("Sorry\n");
			break;
	}
}

void reshape_cb(int x, int y)
{
	double add;
	glViewport(0, 0, x, y);
	width  = x;
	if(y!=0)
		height = y;
	else
		height = 1;
	double aspect_ratio = (double) width / height;
	if(aspect_ratio <= x_dmax/y_dmax)
	{		//necessary "add" to keep proportions
		add = ((x_max - x_min) / 2 - x_dmax); //not 0, in case of change
		x_min += add;					      //form aspect_ratio>x_dmax/y_dmax
		x_max -= add;						  //to aspect_ratio<x_dmax/y_dmax
		add = x_dmax / aspect_ratio - (y_max - y_min) / 2;
		y_min -= add;
		y_max += add;
	}
	else
	{	//necessary "add" to keep proportions
		add = ((y_max - y_min) / 2 - y_dmax); //not 0 from  "<="  -->  ">"
		y_min += add;
		y_max -= add;
		add = y_dmax * aspect_ratio - (x_max - x_min) / 2;
		x_min -= add;
		x_max += add;
	}
}

void display_cb(void)
{
	glClearColor(1., 1., 1., 1.);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(x_min, x_max, y_min, y_max, -1.0, 1.0);

	statistic_update();

	modele_draw(click, clickstart_x, clickstart_y, clickend_x, clickend_y);

	glutSwapBuffers();
}

void keyboard_cb(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'r':
			x_min = y_min = -DMAX;
			x_max = y_max = x_dmax = y_dmax = DMAX;
			reshape_cb(width, height);
			break;
		case 'q':
		case 27:   		//additional possibility to quit
			exit(EXIT_FAILURE);
		case 'k':
		    modele_delete_outside(x_max, x_min, y_max, y_min);
			break;
		case '+':		//additional possibility to zoom in
		case 'p':
			click_position(width * 0.1, height * 0.1, &clickstart_x, &clickstart_y);
			mouse_click_cb(GLUT_LEFT_BUTTON, GLUT_UP, width * 0.9, height * 0.9);
			break;
		case '-':		//additional possibility to zoom out
		case 'm':
			click_position(width * (-0.1), height * (-0.1), &clickstart_x, &clickstart_y);
			mouse_click_cb(GLUT_LEFT_BUTTON, GLUT_UP, width * 1.1, height * 1.1);
			break;
		case 'd':
			if(selected)
				modele_delete_selected(live_entity, element);
			break;
		case 's':
			control_cb(STEP_ID);
			break;
	}
	glutPostRedisplay();
}

void specialkeys_cb(int k, int x, int y) //additional code!!!
{
	switch(k)			//moving in "world" with help of flash-keys
	{
		case GLUT_KEY_UP:
			y_min += y_dmax/10;
			y_max += y_dmax/10;
			break;
		case GLUT_KEY_DOWN:
			y_min -= y_dmax/10;
			y_max -= y_dmax/10;
			break;
		case GLUT_KEY_RIGHT:
			x_min += y_dmax/10;
			x_max += y_dmax/10;
			break;
		case GLUT_KEY_LEFT:
			x_min -= y_dmax/10;
			x_max -= y_dmax/10;
			break;
	}
	glutPostRedisplay();
}

void mouse_click_cb(int button, int button_state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON)
		if(button_state == GLUT_DOWN)	//if down: saves startposition
		{
		    click_position(x, y, &clickstart_x, &clickstart_y);
		    click = 1;
		}
		else     //if up: zoom
		{
			click = 0;
			click_position(x, y, NULL, NULL);
			if(sqrt(pow((clickstart_x - clickend_x), 2)
			   + pow((clickstart_y - clickend_y),2))
			   > EPSIL_CREATION)
				zoom();
		}
	else if(button == GLUT_RIGHT_BUTTON)   //For the final rendu
	{
		double x_pos, y_pos;
		if(button_state == GLUT_DOWN && !move)
		{
			if(live_action)
			{
				click_position(x, y, &x_pos, &y_pos);
				modele_draw_element(live_entity, x_pos, y_pos, &beginnew);
				if(live_entity == AS && beginnew == 1)
					radio_action->set_int_val(0);
			}
			else
				selected = modele_find_nearest(live_entity, &element, 
												x_pos, y_pos);
		}
	}
	glutPostRedisplay();
}

void mouse_motion_cb(int x, int y)
{
	click_position(x, y, NULL, NULL);

	glutPostRedisplay();
}

void click_position(int x, int y, double *xpos, double *ypos)
{
	clickend_x = x_min + (x_max - x_min) * (double)x / width;
	clickend_y = y_max - (y_max - y_min) * (double)y / height;
	if(xpos != NULL && ypos != NULL)
	{
		*xpos = clickend_x;
		*ypos = clickend_y;
	}
}

void zoom(void)
{
	double x = fabs(clickend_x - clickstart_x);
	double y = fabs(clickend_y - clickstart_y);
	double zoom1 = x / (x_max - x_min); //zoom percentage
	double zoom2 = y / (y_max - y_min);
	double add_x = 0, add_y = 0;
	x_dmax = x / 2;
	y_dmax = y / 2;
	if(zoom1 > zoom2)  //takes the axis with less zoom as reference
		add_y = (y - zoom1 * (y_max-y_min)) / -2;
	else
		add_x = (x - zoom2 * (x_max-x_min)) / -2;

	if(clickstart_x < clickend_x) //adjustment of the field of view
	{
		x_min = clickstart_x - add_x;
		x_max = clickend_x   + add_x;
	}
	else
	{
		x_max = clickstart_x + add_x;
		x_min = clickend_x   - add_x;
	}
	if(clickstart_y < clickend_y)
	{
		y_min = clickstart_y - add_y;
		y_max = clickend_y   + add_y;
	}
	else
	{
		y_max = clickstart_y + add_y;
		y_min = clickend_y   - add_y;
	}
}

void statistic_update(void)
{
	char tab[20] = "";

	modele_statistic(statistic);

	sprintf(tab, "%d", statistic[PJ]);
	nb_projecteur->set_text(tab);

	sprintf(tab, "%d", statistic[RF]);
	nb_reflecteur->set_text(tab);

	sprintf(tab, "%d", statistic[AS]);
	nb_absorbeur->set_text(tab);

	sprintf(tab, "%d", statistic[PH]);
	nb_photon->set_text(tab);
}
