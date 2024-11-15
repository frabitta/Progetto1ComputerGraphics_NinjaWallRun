#include "lib.h"
#include "Engine.h"

// variabili globali
const int height = 900, width = 600;
const char windowTitle[] = "Ninja wall run";

// definizione funzioni


int main(void) {
	Engine en;
	if (en.init(height, width, windowTitle) == 0) {
		en.play();
	}
	else {
		cout << "ERROR: failed to start the engine\n" << endl;
	}
	/*
	vector<vec4> v;
	v.push_back(vec4(0.0, 0.745, 0., 1.));
	v.push_back(vec4(-0.2, 0.6, 0., 1.));
	v.push_back(vec4(-0.2, -0.2, 0., 1.));
	v.push_back(vec4(0.0, -1.0, 0., 1.));
	v.push_back(vec4(0.2, -0.2, 0., 1.));
	v.push_back(vec4(0.2, 0.6, 0., 1.));
	v.push_back(vec4(0.0, 0.745, 0., 1.));
	
	mat4 rot = mat4(1.0);
	rot = rotate(rot, radians(90.0f), vec3(0.0, 0.0, 1.0));

	for (int i = 0; i < 7; i++) {
		vec4 r = rot * v.at(i);
		cout << r.x << " " << r.y << endl;
	}
	*/

	return 0;
}