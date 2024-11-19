#pragma once
#include "lib.h"
#include "GraphicComponent.h"
#include "Giocatore.h"
#include "Engine.h"
#include "CollidingEntityCollection.h"

// Forward declaration of Engine class
class Engine;

/* Game World and manager */
class World {
public:
	/* inizializza il mondo: modelli, shaders, ecc. */
	int init(const int height, const int width, Engine* engine);
	/* imposta una nuova partita*/
	void setupNewGame();
	/* aggiorna il mondo */
	void update(float deltaTime);
	/* rendereizza il mondo */
	void render(float time);
	/* termina il gioco */
	void terminate();
	/* sposta il giocatore */
	void INPUT_movePlayer();
private:
	/* dimensions of the world*/
	float world_width;
	/* dimensions of the world*/
	float world_height;
	/* tempo di gioco */
	double world_StartTime;

	/* shader program of the sky backgroud*/
	GLuint skyProg;
	/* shader program of the wall background*/
	GLuint wallProg;
	/* shader program of the entities */
	GLuint entityProg;

	/* GC of the sky background */
	GraphicComponent sky;
	/* GC of the wall background */
	GraphicComponent wall;

	/* player entity */
	Giocatore player;
	/* collection of obstacles */
	CollidingEntityCollection spine;

	/* reference to the running engine */
	Engine* engine;
};