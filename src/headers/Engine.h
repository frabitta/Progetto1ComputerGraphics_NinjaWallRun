#pragma once
#include "lib.h"
#include "World.h"

/* stato del motore di gioco */
enum status {
	active, lost, terminated
};

// Forward declaration of Engine class
class World;

class Engine {
public:
	/* inizializza il motore di gioco*/
	int init(const int height, const int width, const char windowTitle[]);
	/* fa partire il gioco */
	void play();
	/* cambia lo stato della partita in "lost" */
	void gameLost();
	/* termina il motore di gioco */
	int terminate();
	/* is active */
	bool isInGame();
private:
	GLFWwindow* window;
	World* world;
	/* stato del gioco */
	status gameStatus;
	/* loop del gioco in partita */
	void gameplayLoop();
	/* mostra la schermata di morte */
	void showDeathScreen();
	/* inizializza la finestra OpenGL */
	int initializeOpenGLWindow(const int height, const int width, const char windowTitle[]);
};


/* finestra */
/* mondo di gioco */
