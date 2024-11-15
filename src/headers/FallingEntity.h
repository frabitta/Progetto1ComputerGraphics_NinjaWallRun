#pragma once
#include "lib.h"
#include "CollidingEntity.h"
#include "GraphicComponent.h"

class FallingEntity : public CollidingEntity {
public:
	/* inizializza le strutture */
	void init(GLuint uniformModelMatrix, GraphicComponent gc, vec2 pos, float fallingSpeed);

	/* aggiorna lo stato del giocatore*/
	void update(float deltaTime);

	/* renderizza il giocatore */
	void render(float time);

	/* cleans all the structures */
	void destroy();

	/* is visible */
	bool isOnScreen();
private:
	GraphicComponent gc;
	float fallingSpeed;
	bool onScreen = true;
};