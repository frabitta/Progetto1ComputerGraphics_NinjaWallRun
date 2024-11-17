#pragma once
#include "lib.h"
#include "GraphicComponent.h"
#include "CollidingEntity.h"

/* stati nelle quali il Giocatore si può trovare durante la partita (posizione) */
enum stati {l, moving_r, r, moving_l};

/* entità del giocatore */
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

	/* setups for a new game */
	void startGame();
private:
	/* stato attuale */
	stati stato;
	/* posizione nel mondo per stare sulla parete di sinistra*/
	vec2 leftPos;
	/* posizione nel mondo per stare sulla parete di destra*/
	vec2 rightPos;
	/* punteggio vita */
	int vita;
};