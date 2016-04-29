/*!
 \file graphic.h
 \brief Module to draw
 \author Natal Willisch and Jérôme Scyboz
 \version 1.10.1
 \date 19 april 2016
 */

#ifndef GRAPHIC_H
#define GRAPHIC_H

//DRAWS A CIRCLE (actually a regular polygon with nb_sides corners)
void graphic_draw_circle (double center_x, double center_y, float radius, int nb_sides);

//DRAWS 1 OR MUTLTIPLE SEGMENT(S)
void graphic_draw_segments (double pos1_x, double pos1_y,
                            double pos2_x, double pos2_y);

//DRAWS A RECTANGLE (DEFINED BY A DIAGONAL)
void graphic_draw_rectangle (double pos1_x, double pos1_y,
                             double pos2_x, double pos2_y);

//SETS COLOR (in 3 floats and one float-table variant)
void graphic_set_color3f(float r, float g, float b);
void graphic_set_color3fv(const float color[3]);

//SETS LINEWIDTH
void graphic_set_line_width(float width);

#endif
