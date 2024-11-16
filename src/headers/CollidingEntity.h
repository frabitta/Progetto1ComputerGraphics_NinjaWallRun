#pragma once
#include "lib.h"
#include "BoundingBox.h"
#include "GraphicComponent.h"

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
	BoundingBox BB;
	vec2 position = vec2(0.,0.);
	float size = 1.0f;
	float angle = 0;
	bool mirror = false;
	mat4 Model = mat4(1.0f);

	GLuint shaderProg;
	GLuint uniformModelMatrix;
	vector<GraphicComponent> graphicList;

	void updateMatrix();
};