#pragma once
#include "lib.h"
#include "CollidingEntity.h"
#include "BoundingBox.h"

/* collezione di CollidingEntities */
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
	/* lista delle entità gestite */
	vector<CollidingEntity*> entityList;
	/* lista delle entità da escludere dalle collisioni */
	vector<bool> ignoreList;
};