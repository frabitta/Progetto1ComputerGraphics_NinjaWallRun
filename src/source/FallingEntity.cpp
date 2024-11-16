#include "FallingEntity.h"

void FallingEntity::init(GLuint shaderProg, GLuint uniformModelMatrix, GraphicComponent gc, vec2 pos, float fallingSpeed) {
	vector<GraphicComponent> gcList;
	gcList.push_back(gc);
	CollidingEntity::init(shaderProg, uniformModelMatrix, gcList);

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
		CollidingEntity::render(time);
	}
}

void FallingEntity::destroy() {
	this->onScreen = false;
}

bool FallingEntity::isOnScreen() {
	return this->onScreen;
}