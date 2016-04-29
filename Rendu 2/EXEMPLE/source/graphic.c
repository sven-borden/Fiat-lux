/*!
 \file graphic.c
 \brief Module to draw
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 19 april 2016
 */

#include <stdio.h>
#include <math.h>
#include <GL/glu.h>
#include "graphic.h"

#define _USE_MATH_DEFINES

void graphic_draw_circle (double center_x, double center_y, float radius, int nb_sides)
{
	int i = 0;

	float alpha;
	float x;
	float y;

	glBegin (GL_LINE_LOOP);

	for (i = 0; i < nb_sides; i++)
	{
		alpha = i * 2. * M_PI / nb_sides;
		x = center_x + radius * cos(alpha);
		y = center_y + radius * sin(alpha);
		glVertex2f(x ,y);
	}

	glEnd ();
}

void graphic_draw_segments (double pos1_x, double pos1_y,
                            double pos2_x, double pos2_y)
{
	int i = 0;

    glBegin (GL_LINE_STRIP);

    glVertex2f(pos1_x, pos1_y);
    glVertex2f(pos2_x, pos2_y);

	glEnd ();
}

void graphic_draw_rectangle (double pos1_x, double pos1_y,
                             double pos2_x, double pos2_y)
{
    glBegin (GL_LINE_LOOP);

    glVertex2f (pos1_x, pos1_y);
    glVertex2f (pos2_x, pos1_y);
    glVertex2f (pos2_x, pos2_y);
    glVertex2f (pos1_x, pos2_y);

    glEnd ();
}

void graphic_set_color3f(float r, float g, float b)
{
  glColor3f(r, g, b);
}

void graphic_set_color3fv(const float color[3])
{
  glColor3fv(color);
}

void graphic_set_line_width(float width)
{
  glLineWidth(width);
}


