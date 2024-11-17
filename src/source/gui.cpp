#include "gui.h"

Engine* runningEngine;
void GUI_Initialize(GLFWwindow* window, Engine* engine) {
    runningEngine = engine;
    // Verifica la compatibilità della versione di ImGui
    IMGUI_CHECKVERSION();

    // Create ImGui context
    ImGuiContext * cntx = ImGui::CreateContext(); // Crea un nuovo contesto ImGui
    ImGui::SetCurrentContext(cntx);

    // Get ImGui IO object to configure options
    ImGuiIO& io = ImGui::GetIO(); // Ottieni l'oggetto IO per configurare opzioni come input, font e stili
    io.FontGlobalScale = 2.0f;  //Dimensione del font
    // Set dark theme
    ImGui::StyleColorsDark(); // Imposta il tema scuro per l'interfaccia

    // Initialize ImGui for GLFW and OpenGL 3.3
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Inizializza ImGui per GLFW
    ImGui_ImplOpenGL3_Init("#version 330 core"); // Inizializza ImGui per OpenGL 3.3
}

void GUI_lostMenu(void /*int punteggio*/) {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame(); // Inizia un nuovo frame per ImGui
    ImGui::NewFrame();

    // Create a window for color settings
    ImGui::Begin("wanna play?");

    ImGui::Text("YOU LOST");

    if (ImGui::Button("play again")) {
        runningEngine->playAgain();
    }

    if (ImGui::Button("quit")) {
        runningEngine->terminate();
    }
    
    ImGui::End(); // Termina la finestra
    // Render ImGui
    ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui
}

void GUI_close(void) {
    ImGui_ImplOpenGL3_Shutdown(); // Chiude l'integrazione con OpenGL
    ImGui_ImplGlfw_Shutdown(); // Chiude l'integrazione con GLFW
    ImGui::DestroyContext(); // Distrugge il contesto ImGui
}
