#include "Giocatore.h"
#include "geometrie.h"

void Giocatore::init(GLuint shaderProg, GLuint uniformModelMatrix, vec2 leftPos, vec2 rightPos) {
	CollidingEntity::init(uniformModelMatrix);
	this->leftPos = leftPos;
	this->rightPos = rightPos;

	vector<vec3> vertici = {};
	vector<vec4> colori = {};

	init_curvaHModel(vertici, colori, "scarfModel.txt");
	this->scarfGC.loadVertices(vertici, colori, GL_TRIANGLE_FAN, shaderProg);

	init_curvaHModel(vertici, colori, "playerModel.txt");
	this->playerGC.loadVertices(vertici, colori, GL_TRIANGLE_FAN, shaderProg);
	this->BB.generateFromVector(vertici);

	this->vita = 1;
	this->stato = l;
	this->position = this->leftPos;
	this->size = 40;
	this->angle = -90.0f;
	this->mirror = true;
	this->updateMatrix();
}

const float speed = 1500;
void Giocatore::update(float deltaTime) {
	bool changed = false;
	switch (this->stato) {
	case moving_r:
		this->position.x += speed * deltaTime;
		changed = true;
		break;
	case moving_l:
		this->position.x -= speed * deltaTime;
		changed = true;
		break;
	default:
		break;
	}

	if (this->position.x >= this->rightPos.x) {
		this->position.x = this->rightPos.x;
		this->stato = r;
		this->angle = 90.0f;
		this->mirror = false;
		changed = true;
	}
	else if (this->position.x <= this->leftPos.x) {
		this->position.x = this->leftPos.x;
		this->stato = l;
		this->angle = -90.0f;
		this->mirror = true;
		changed = true;
	}

	if (changed) {
		this->updateMatrix();
	}
}

void Giocatore::render(float time) {
	glUniformMatrix4fv(this->uniformModelMatrix, 1, GL_FALSE, value_ptr(this->Model));

	this->playerGC.render();
	this->scarfGC.render();
}

void Giocatore::changeLato() {
	if (this->stato == l) {
		this->angle = 0;
		this->mirror = false;
		this->stato = moving_r;
	}
	if (this->stato == r) {
		this->angle = 0;
		this->mirror = true;
		this->stato = moving_l;
	}
}

void Giocatore::destroy() {
	this->playerGC.deleteBuffers();
	this->scarfGC.deleteBuffers();
}

bool Giocatore::checkCollision(BoundingBox bb) {
	return this->BB.checkCollision(bb);
}

bool Giocatore::isAlive() {
	return this->vita > 0;
}

void Giocatore::takeDamage() {
	this->vita--;
}