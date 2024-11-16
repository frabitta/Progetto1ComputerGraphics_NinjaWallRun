#pragma once
#include "lib.h"
#include "CollidingEntity.h"
#include "BoundingBox.h"

class CollidingEntityCollection {
public:
	/* initializes the collection */
	void init();
	/* updates all elements*/
	void update(float deltaTime);
	/* renders all the elementes*/
	void render(float time);
	/* returns the list of bounding boxes */
	vector<BoundingBox> getBBlist();
	/* pushes a new entity in the collection */
	void push(CollidingEntity* newEntity);
	/* sets the i-th entity to be ignored (not returned in the BB collection)*/
	void ignore(int i);
	/* removes the i-th entity from the collection */
	void erase(int i);
	/* destroys the whole collection */
	void destroy();
private:
	vector<CollidingEntity*> entityList;
	vector<bool> ignoreList;
};