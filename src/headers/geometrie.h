#pragma once
#include "lib.h"
#include "GraphicComponent.h"

#define CURVE_FOLDER "rsc/curve/"

/* sets the vertices of a plane defined by twoi opposite points */
void init_plane(vector<vec3>& vertici, vector<vec4>& colori, vec2 btm_left, vec2 top_right, vec4 color);

/* sets the vertices of a triangle (WITH THE CENTER AT ITS BASE) */
void init_triangle(vector<vec3>& vertici, vector<vec4>& colori, vec4 color);

/* // ovale */
void init_oval(vector<vec3>& vertici, vector<vec4>& colori, float a, float b, vec4 color);

/* // shuriken */
void init_shuriken(vector<vec3>& vertici, vector<vec4>& colori, vec4 colorCenter, vec4 colorBorder);

/* crea un modello coi contorni definiti da una curva di hermite
* curvaFileName - nome del file contenente i dati delle curve:
*	numero Control points
*	punto centrale, colore punto
*	coordinate punto contorno, colore punto
*	coordinate punto contorno, colore punto
*	coordinate punto contorno, colore punto
*	coordinate punto contorno, colore punto
*	...
*/
void init_curvaHModel(vector<vec3>& vertici, vector<vec4>& colori, const char* curvaFileName);