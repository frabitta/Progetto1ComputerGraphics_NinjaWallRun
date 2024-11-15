#include "CollidingEntity.h"

BoundingBox CollidingEntity::getBB() {
	return this->BB;
}

void CollidingEntity::updateMatrix() {
	mat4 mat = mat4(1.0f);
	mat = translate(mat, vec3(this->position.x, this->position.y, 0.));
	mat = scale(mat, vec3(this->size, this->size, 1.));
	mat = rotate(mat, radians(this->angle), vec3(0., 0., 1.));
	if (this->mirror) {
		mat = rotate(mat, radians(180.0f), vec3(0., 1., 0.));
	}
	this->Model = mat;

	this->BB.updateMat(this->Model);
	glUniformMatrix4fv(this->uniformModelMatrix, 1, GL_FALSE, value_ptr(this->Model));
}

void CollidingEntity::init(GLuint uniformModelMatrix) {
	this->uniformModelMatrix = uniformModelMatrix;
}