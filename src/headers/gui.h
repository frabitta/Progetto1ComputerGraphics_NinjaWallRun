#pragma once
#include "lib.h"
#include "Engine.h"

/* Initializes Imgui context */
void GUI_Initialize(GLFWwindow* window, Engine* engine);

/* visualizes the Lost menu */
void GUI_lostMenu(void);

/* closes the imgui context */
void GUI_close(void);
