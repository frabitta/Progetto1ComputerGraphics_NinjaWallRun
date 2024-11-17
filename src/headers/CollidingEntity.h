#pragma once
#include "lib.h"
#include "BoundingBox.h"
#include "GraphicComponent.h"

/* Entità capace di collidere con altre */
class CollidingEntity {
public:
	/* inizializza le strutture */
	void init(GLuint shaderProg, GLuint uniformModelMatrix, vector<GraphicComponent> graphicList);

	/* aggiorna lo stato del giocatore*/
	virtual void update(float deltaTime) = 0;

	/* renderizza il giocatore */
	void render(float time);

	/* cleans all the structures */
	void destroy();

	/* returns the bounding box of the entity*/
	BoundingBox getBB();
	
	/* returns if the entity is still alive */
	virtual bool isAlive() = 0;
protected:
	/* Bounding box dell'entità */
	BoundingBox BB;
	/* posizione nel mondo */
	vec2 position = vec2(0.,0.);
	/* dimensione */
	float size = 1.0f;
	/* rotazione */
	float angle = 0;
	/* riflessione */
	bool mirror = false;
	/* matrice di modellazione */
	mat4 Model = mat4(1.0f);
	/* shader program usata */
	GLuint shaderProg;
	/* variabile uniform di modellazione */
	GLuint uniformModelMatrix;
	/* lista di componenti grafici che rappresentano l'entità */
	vector<GraphicComponent> graphicList;
	/* aggiorna la matrice di modellazione sulla base dei parametri dell'entità */
	void updateMatrix();
};