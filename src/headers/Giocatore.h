#pragma once
#include "lib.h"
#include "GraphicComponent.h"
#include "CollidingEntity.h"

enum stati {l, moving_r, r, moving_l};

class Giocatore: public CollidingEntity {
public:
	/* inizializza le strutture */
	void init(GLuint shaderProg, GLuint uniformModelMatrix, vec2 leftPos, vec2 rightPos);

	/* aggiorna lo stato del giocatore*/
	void update(float deltaTime);

	/* triggera il cambio di lato*/
	void changeLato();

	/* dice se il player collide con una entity*/
	bool checkCollision(BoundingBox bb);

	/* returns if the entity is still alive */
	bool isAlive();

	/* takes damage */
	void takeDamage();
private:
	stati stato;
	vec2 leftPos;
	vec2 rightPos;
	int vita;
};