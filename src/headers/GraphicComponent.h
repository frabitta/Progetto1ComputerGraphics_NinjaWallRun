#pragma once
#include "lib.h"

/* graphic component of world elements*/
class GraphicComponent {
public: 
    /* load the vertices that define the gc and how to render them (primitive and shader program) */
    void loadVertices(vector<vec3> vertici, vector<vec4> colori, GLenum primitiva, unsigned int shaderProg);
    /* renders the GC */
    void render();
    /* deletes the structures allocated */
    void deleteBuffers();
    /* returns a vector of the vertices currently loaded */
    vector<vec3> getVertices();
private:

    GLuint VAO;             // identificatore del Vertex Array Object (VAO)
    GLuint VBO_vertices;    // identificatore del Vertex Buffer Object (VBO): contiene le coordinate dei vertici dell'oggetto.
    GLuint VBO_colors;      // identificatore del VBO che contiene i colori dei vertici dell'oggetto.

    // vertices
    vector<vec3> vertices;  // vector contenente le coordinate dei vertici  (x,y,<)
    vector<vec4> colors;    // vector contenente i colori dei vertici dell'oggetto  RGBA(red, green, blue, alpha).

    int nV;                 // numero di vertici
    GLenum primitiva;             // specifica che primitiva di rendering usare
    unsigned int shaderProg;  // specifica quale programma di shaders usare

    void initVAO();
};