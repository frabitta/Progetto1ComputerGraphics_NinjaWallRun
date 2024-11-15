#include "FallingEntity.h"

void FallingEntity::init(GLuint uniformModelMatrix, GraphicComponent gc, vec2 pos, float fallingSpeed) {
	CollidingEntity::init(uniformModelMatrix);
	this->uniformModelMatrix = uniformModelMatrix;
	this->gc = gc;
	this->position = pos;
	this->fallingSpeed = fallingSpeed;
	this->size = 50;
	this->updateMatrix();
	/*
	BoundingBox BB;
	float angle = 0;
	bool mirror = false;
	*/
}

void FallingEntity::update(float deltaTime) {
	this->position.y -= this->fallingSpeed * deltaTime;
	if (this->position.y <= -this->size * 2) {
		this->destroy();
		return;
	}
	this->updateMatrix();
}

void FallingEntity::render(float time) {
	if (this->isOnScreen()) {
		glUniformMatrix4fv(this->uniformModelMatrix, 1, GL_FALSE, value_ptr(this->Model));
		this->gc.render();
	}
}

void FallingEntity::destroy() {
	this->onScreen = false;
}

bool FallingEntity::isOnScreen() {
	return this->onScreen;
}