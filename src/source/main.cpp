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
	return 0;
}