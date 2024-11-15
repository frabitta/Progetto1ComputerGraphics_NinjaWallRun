#include "Engine.h"
#include "lib.h"
#include "World.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// used by the callbacks
static Engine* engine;
static World* engineWorld;

// public ----------------------------------------------------------------------------
int Engine::init(const int height, const int width, const char windowTitle[]) {
    engine = this;

    // init window
    int success = initializeOpenGLWindow(height, width, windowTitle);
    if (success != 0) {
        return success;
    }
    // init world
    this->world = new World();
    success = this->world->init(height,width,this);
    if (success != 0) {
        return success;
    }
    engineWorld = this->world;
    // keyboard callback
    glfwSetKeyCallback(window, key_callback);
    // mouse press callback (shuriken)

    this->gameStatus = active;

    return 0;
};

void Engine::play() {
    while (this->gameStatus != terminated) {
        switch (this->gameStatus)
        {
        case active:
            // pulisci tutto prima della prossima partita
            this->world->setupNewGame();
            this->gameplayLoop();
            break;
        case lost:
            this->showDeathScreen();
            break;
        default:
            break;
        }
    }
    this->terminate();
}

void Engine::gameLost() {
    this->gameStatus = lost;
}

int Engine::terminate() {
    this->world->terminate();
    glfwTerminate();
    return 0;
}

// private ----------------------------------------------------------------------------------------

/*
* loads openGl using glfw-glad and creates the window
*/
int Engine::initializeOpenGLWindow(const int height, const int width, const char windowTitle[]) {
    /* Inizializza la libreria */
    if (!glfwInit())   //se glfwInit() d� valore falso, return -1
        return -1;

    //Imposta le propriet� del contesto e del profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    //Abilita il double buffering, disabilita ridimensionamento
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    this->window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
    if (!this->window)
    {
        cout << "ERROR: Failed to create the window !" << endl;
        glfwTerminate(); //Libera le risorse allcoata da glfwInit
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(this->window); //crea il context corrente e lo associa a window. In opengl un rendering context � una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico

    //verifica se la libreria GLAD � riuscita a caricare correttamente tutti i puntatori
    // alle funzioni OpenGL necessarie.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR: Failed to load opengl function pointers!" << std::endl;
        glfwTerminate();
        return -1;
    }
    return 0;
}

void Engine::gameplayLoop() {
    float oldFrame = 0.0f;
    // float oldFrame = glfwGetTime();
    while (!glfwWindowShouldClose(window) && this->gameStatus == active) {
        /* Poll for and process events */
        glfwPollEvents();
        
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - oldFrame;

        this->world->update(deltaTime);
        this->world->render(currentFrame);
        
        glClearColor(1.0f, 0.0, 0.0, 1.0f);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        oldFrame = currentFrame;
    }
    if (this->gameStatus != lost) {
        this->gameStatus = terminated;
    }
}

/*
* ferma il gioco e mostra un menu con:
* - punteggio
* - record
* - riprova -> gamestatus = active
* - esci -> gamestatus = terminated
* 
* ora se perdi termina
* 
* TODO
*/
void Engine::showDeathScreen() {
    this->gameStatus = terminated;
}

bool Engine::isInGame() {
    return this->gameStatus == active;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!engine->isInGame()) {
        return;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        engineWorld->INPUT_movePlayer();
    }
}