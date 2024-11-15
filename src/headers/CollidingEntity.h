#pragma once
#include "lib.h"
#include "BoundingBox.h"

class CollidingEntity {
public:
	/* inizializza le strutture */
	void init(GLuint uniformModelMatrix);

	/* aggiorna lo stato del giocatore*/
	virtual void update(float deltaTime) = 0;

	/* renderizza il giocatore */
	virtual void render(float time) = 0;

	/* cleans all the structures */
	virtual void destroy() = 0;

	/* returns the bounding box of the entity*/
	BoundingBox getBB();
protected:
	BoundingBox BB;
	vec2 position = vec2(0.,0.);
	float size = 1.0f;
	float angle = 0;
	bool mirror = false;
	mat4 Model = mat4(1.0f);
	GLuint uniformModelMatrix;

	void updateMatrix();
};