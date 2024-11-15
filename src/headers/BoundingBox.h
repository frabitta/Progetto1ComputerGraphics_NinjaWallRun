#pragma once
#include "lib.h"

class BoundingBox {
public:
	/* returns if the local BB collides with bb*/
	bool checkCollision(BoundingBox bb);

	/* loads the vertices of the box*/
	void loadLocalVert(vec2 down_left, vec2 top_right);

	/* generates the BB from a list of points*/
	void generateFromVector(vector<vec3> points);

	/* updates the world coordinates*/
	void updateMat(mat4 trasformMatrix);

	/* gets the world coordinates*/
	void getWorldVert(vec2 &down_left, vec2 &top_right);
private:
	vec2 LOCAL_down_left;
	vec2 LOCAL_top_right;
	mat4 trasformMatrix = mat4(1.0f);
	vec2 WORLD_down_left;
	vec2 WORLD_top_right;

	void updateVert();
};
