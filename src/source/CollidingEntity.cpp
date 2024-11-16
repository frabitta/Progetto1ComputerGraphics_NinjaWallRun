#include "CollidingEntity.h"

BoundingBox CollidingEntity::getBB() {
	return this->BB;
}

void CollidingEntity::updateMatrix() {
	mat4 mat = mat4(1.0f);
	mat = translate(mat, vec3(this->position.x, this->position.y, 0.));
	mat = scale(mat, vec3(this->size, this->size, 1.));
	this->BB.updateMat(mat);		// the BB must not rotate otherwise the check doesn't work
	
	mat = rotate(mat, radians(this->angle), vec3(0., 0., 1.));
	if (this->mirror) {
		mat = rotate(mat, radians(180.0f), vec3(0., 1., 0.));
	}
	this->Model = mat;
}

void CollidingEntity::render(float time) {
	glUseProgram(this->shaderProg);
	// glUniform1f(this->uniformTime, time);
	glUniformMatrix4fv(this->uniformModelMatrix, 1, GL_FALSE, value_ptr(this->Model));
	for (int i = 0; i < this->graphicList.size(); i++) {
		this->graphicList[i].render();
	}
}

void CollidingEntity::init(GLuint shaderProg, GLuint uniformModelMatrix, vector<GraphicComponent> graphicList) {
	this->shaderProg = shaderProg;
	this->uniformModelMatrix = uniformModelMatrix;
	this->graphicList = graphicList;
}

void CollidingEntity::destroy() {
	for (int i = 0; i < this->graphicList.size(); i++) {
		this->graphicList[i].deleteBuffers();
	}
}