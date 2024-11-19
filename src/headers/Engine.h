#pragma once
#include "lib.h"
#include "World.h"

/* stato del motore di gioco */
enum status {
	active, lost, terminated, paused
};

// Forward declaration of Engine class
class World;

/* Motore del gioco, gestisce finestra, mondo di gioco, interazioni */
class Engine {
public:
	/* inizializza il motore di gioco*/
	int init(const int height, const int width, const char windowTitle[]);
	/* fa partire il gioco */
	void play();
	/* cambia lo stato della partita in "lost" */
	void gameLost(int punteggio);
	/* cambia lo stato in "active" per far partire una nuova partita dopo aver perso */
	void playAgain();
	/* termina il motore di gioco */
	void terminate();
	/* is active */
	bool isInGame();
	/* pauses the engine, it does nothing until the status changes*/
	void pause();
private:
	/* finestra creata */
	GLFWwindow* window;
	/* mondo di gioco in uso*/
	World* world;
	/* stato del gioco */
	status gameStatus;
	/* loop del gioco in partita */
	void gameplayLoop();
	/* mostra la schermata di morte */
	void showDeathScreen(float pausedTime, int punteggio);
	/* inizializza la finestra OpenGL */
	int initializeOpenGLWindow(const int height, const int width, const char windowTitle[]);
	/* chiude il motore */
	int close();
};
