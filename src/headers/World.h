#pragma once
#include "lib.h"
#include "GraphicComponent.h"
#include "Giocatore.h"
#include "Engine.h"

// Forward declaration of Engine class
class Engine;

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
	float world_width;
	float world_height;

	GLuint skyProg;
	GLuint wallProg;
	GLuint entityProg;

	GraphicComponent sky;
	GraphicComponent wall;

	Giocatore player;

	Engine* engine;
};