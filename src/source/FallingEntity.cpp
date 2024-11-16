#include "FallingEntity.h"

void FallingEntity::init(GLuint shaderProg, GLuint uniformModelMatrix, GraphicComponent gc, vec2 pos, float fallingSpeed) {
	vector<GraphicComponent> gcList;
	gcList.push_back(gc);
	CollidingEntity::init(shaderProg, uniformModelMatrix, gcList);

	vec2 offset = vec2(30,0);
	this->position = pos + offset;
	this->fallingSpeed = fallingSpeed;
	this->size = 50;
	this->angle = -90;
	this->updateMatrix();

	this->BB.generateFromVector(gc.getVertices());
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