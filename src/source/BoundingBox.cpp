#include "BoundingBox.h"

bool BoundingBox::checkCollision(BoundingBox bb) {
	vec2 a_dl = this->WORLD_down_left;
	vec2 a_tr = this->WORLD_top_right;
	vec2 b_dl, b_tr;
	bb.getWorldVert(b_dl, b_tr);

	return a_dl.x <= b_tr.x && a_tr.x >= b_dl.x
		&& a_dl.y <= b_tr.y && a_tr.y >= b_dl.y;
}

void BoundingBox::loadLocalVert(vec2 down_left, vec2 top_right) {
	this->LOCAL_down_left = down_left;
	this->LOCAL_top_right = top_right;
	this->updateVert();
}

void BoundingBox::updateMat(mat4 trasformMatrix) {
	this->trasformMatrix = trasformMatrix;
	this->updateVert();
}

void BoundingBox::getWorldVert(vec2& down_left, vec2& top_right) {
	down_left = this->WORLD_down_left;
	top_right = this->WORLD_top_right;
}

void BoundingBox::updateVert() {
	vec4 dl = vec4(this->LOCAL_down_left.x, this->LOCAL_down_left.y, 0., 1.);
	vec4 tr = vec4(this->LOCAL_top_right.x, this->LOCAL_top_right.y, 0., 1.);
	vec4 Wdl = this->trasformMatrix * dl;
	vec4 Wtr = this->trasformMatrix * tr;

	this->WORLD_down_left = vec2(Wdl.x, Wdl.y);
	this->WORLD_top_right = vec2(Wtr.x, Wtr.y);
}

#define MAX 99999999
void BoundingBox::generateFromVector(vector<vec3> points) {
	float bottom = MAX, top = -MAX;
	float left = MAX, right = -MAX;
	for (int i = 0; i < points.size(); i++) {
		if (points[i].x < left) {
			left = points[i].x;
		}
		if (points[i].x > right) {
			right = points[i].x;
		}
		if (points[i].y < bottom) {
			bottom = points[i].y;
		}
		if (points[i].y > top) {
			top = points[i].y;
		}
	}

	this->loadLocalVert(vec2(left,bottom), vec2(right,top));
}
