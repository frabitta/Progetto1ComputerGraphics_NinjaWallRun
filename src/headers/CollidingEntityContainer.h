#pragma once
#include "lib.h"
#include "CollidingEntity.h"
#include "GraphicComponent.h"

class CollidingEntityContainer {
public:
	/* initializes the structure, using cg as GraphicsComponent */
	void init(GraphicComponent gc);
	/* updates all the elements of the collection*/
	void update();
	/* renders all the elements*/
	void render();
	/* destroys the structure*/
	void destroy();
	/* returns all the BoundigBoxes of all elements*/
	vector<BoundingBox> getBBlist();
	/* pushes a new element at position pos*/
	void push(vec2 pos);
	/* deletes i-th element*/
	void erase(int i);
private:
	vector<CollidingEntity> entityList;
	GraphicComponent graphComp;
};