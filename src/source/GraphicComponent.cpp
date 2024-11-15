#include "GraphicComponent.h"

void GraphicComponent::loadVertices(vector<vec3> vertici, vector<vec4> colori, GLenum primitiva, unsigned int shaderProg) {
    this->vertices = vertici;
    this->colors = colori;
    this->nV = vertices.size();
    this->primitiva = primitiva;
    this->shaderProg = shaderProg;

	this->initVAO();
}

void GraphicComponent::render() {
    glUseProgram(this->shaderProg);
    glBindVertexArray(this->VAO);
    glDrawArrays(this->primitiva, 0, this->nV);
}

void GraphicComponent::initVAO() {
    // creo il VAO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    // creo, popolo e attivo il VBO dei vertici
    glGenBuffers(1, &this->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vec3), this->vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // creo, popolo e attivo il VBO dei colori
    glGenBuffers(1, &this->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void GraphicComponent::deleteBuffers() {
    glDeleteBuffers(1, &this->VBO_vertices);
    glDeleteBuffers(1, &this->VBO_colors);
    glDeleteVertexArrays(1, &this->VAO);
}
