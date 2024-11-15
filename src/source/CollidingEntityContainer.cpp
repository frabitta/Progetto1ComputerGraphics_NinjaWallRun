#include "CollidingEntityContainer.h"

void CollidingEntityContainer::init(GraphicComponent gc) {
	this->graphComp = gc;
}

void CollidingEntityContainer::update() {

}

void CollidingEntityContainer::render() {

}

void CollidingEntityContainer::destroy() {

}

vector<BoundingBox> CollidingEntityContainer::getBBlist() {
	return vector<BoundingBox>();
}

void CollidingEntityContainer::push(vec2 pos) {

}

void CollidingEntityContainer::erase(int i) {

}