#include "CollidingEntityCollection.h"

void CollidingEntityCollection::init() {
	this->entityList.clear();
	this->ignoreList.clear();
}

void CollidingEntityCollection::update(float deltaTime) {
	for (int i = 0; i < this->entityList.size(); i++) {
		this->entityList[i]->update(deltaTime);
		if (!this->entityList[i]->isAlive()) {
			this->erase(i);
		}
	}
}

void CollidingEntityCollection::render(float time) {
	for (int i = 0; i < this->entityList.size(); i++) {
		this->entityList[i]->render(time);
	}
}

vector<BoundingBox> CollidingEntityCollection::getBBlist() {
	vector<BoundingBox> bbList;
	for (int i = 0; i < this->entityList.size(); i++) {
		if (!this->ignoreList[i]) {
			bbList.push_back(this->entityList[i]->getBB());
		}
	}
	return bbList;
}

void CollidingEntityCollection::push(CollidingEntity* newEntity) {
	this->entityList.push_back(newEntity);
	this->ignoreList.push_back(false);
}

void CollidingEntityCollection::ignore(int i) {
	this->ignoreList[i] = true;
}

void CollidingEntityCollection::erase(int i) {
	this->entityList.erase(this->entityList.begin() + i);
}

void CollidingEntityCollection::destroy() {
	for (int i = 0; i < this->entityList.size(); i++) {
		this->entityList[i]->destroy();
	}
}