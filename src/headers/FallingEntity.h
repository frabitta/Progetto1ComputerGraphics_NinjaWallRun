#pragma once
#include "lib.h"
#include "CollidingEntity.h"
#include "GraphicComponent.h"

/* entità che cade nel mondo */
class FallingEntity : public CollidingEntity {
public:
	/* inizializza le strutture */
	void init(GLuint shaderProg, GLuint uniformModelMatrix, GraphicComponent gc, vec2 pos, bool right, float fallingSpeed);

	/* aggiorna lo stato del giocatore*/
	void update(float deltaTime);

	/* renderizza il giocatore */
	void render(float time);

	/* cleans all the structures */
	void destroy();

	/* returns if the entity is still alive */
	bool isAlive();
private:
	/* velocità di caduta */
	float fallingSpeed = 10.0;
	/* se ancora visibile */
	bool onScreen = true;
};