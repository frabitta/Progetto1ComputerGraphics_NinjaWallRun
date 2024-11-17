#include "World.h"
#include "ShaderMaker.h"
#include "GraphicComponent.h"
#include "geometrie.h"

#include "FallingEntity.h"

#define SHADER_SFONDO_VERT "sfondoVert.glsl"
#define SHADER_CIELO_FRAG "cieloFrag.glsl"
#define SHADER_MURO_FRAG "muroFrag.glsl"

#define SHADER_ENTITY_VERT "entityVert.glsl"
#define SHADER_ENTITY_FRAG "entityFrag.glsl"

const float bg_R = 0.025, bg_G = 0.020, bg_B = 0.11;
const vec4 bg_color = vec4(bg_R, bg_G, bg_B, 1.0);
GLuint UNI_skyProg_screenRes, UNI_skyProg_currentTime;
GLuint UNI_wallProg_screenRes, UNI_wallProg_currentTime, UNI_wallProg_offset;
GLuint UNI_entity_MatProj, UNI_entity_MatModel;

GraphicComponent spinaGC;
vec2 leftWallPos;
vec2 rightWallPos;

float maxSpeed = 700.0;
float fallingSpeed = 300.0;
float speedIncrease = 5.0;
float genDelta = 2.0;
float genDecrease = 0.1;

float randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

int World::init(const int height, const int width, Engine* engine) {
	this->engine = engine;
	this->world_width = width;
	this->world_height = height;
	vector<vec3> vertici = {};
	vector<vec4> colori = {};

	// init shaders ------------------------
	this->skyProg = ShaderMaker::createProgram(SHADER_SFONDO_VERT, SHADER_CIELO_FRAG);
	this->wallProg = ShaderMaker::createProgram(SHADER_SFONDO_VERT, SHADER_MURO_FRAG);
	this->entityProg = ShaderMaker::createProgram(SHADER_ENTITY_VERT, SHADER_ENTITY_FRAG);
	
	// init uniforms -----------------------
	// sky
	glUseProgram(skyProg);
	UNI_skyProg_screenRes = glGetUniformLocation(skyProg, "resolution");
	UNI_skyProg_currentTime = glGetUniformLocation(skyProg, "currentTime");
	glUniform2fv(UNI_skyProg_screenRes, 1, value_ptr(vec2(width, height)));
	// wall
	glUseProgram(wallProg);
	UNI_wallProg_screenRes = glGetUniformLocation(skyProg, "resolution");
	UNI_wallProg_currentTime = glGetUniformLocation(skyProg, "currentTime");
	UNI_wallProg_offset = glGetUniformLocation(skyProg, "offset");
	glUniform2fv(UNI_skyProg_screenRes, 1, value_ptr(vec2(width, height)));
	// entity
	glUseProgram(entityProg);
	UNI_entity_MatProj = glGetUniformLocation(entityProg, "Projection");
	UNI_entity_MatModel = glGetUniformLocation(entityProg, "Model");
	mat4 proj = ortho(0.0f,this->world_width,0.0f,this->world_height);
	glUniformMatrix4fv(UNI_entity_MatProj, 1, GL_FALSE, value_ptr(proj));

	// init sfondo -------------------------
	// sky
	init_plane(vertici, colori, vec2(-1.,-1.), vec2(1.,1.), bg_color);
	this->sky.loadVertices(vertici, colori, GL_TRIANGLE_FAN, skyProg);
	// wall
	init_plane(vertici, colori, vec2(-1., -1.), vec2(1., 1.), vec4(1.,0.,0.,1.));
	this->wall.loadVertices(vertici, colori, GL_TRIANGLE_FAN, wallProg);
	
	// init entities -----------------------
	leftWallPos = vec2(this->world_width * 0.11, this->world_width * 0.10);
	rightWallPos = vec2(this->world_width - this->world_width * 0.11, this->world_width * 0.10);
	// player
	this->player.init(entityProg, UNI_entity_MatModel, leftWallPos, rightWallPos);
	// spina GC
	vertici.clear();
	vertici.push_back(vec3(-1, -1, 0));
	vertici.push_back(vec3(1, -1, 0));
	vertici.push_back(vec3(0, 1, 0));
	colori.clear();
	colori.push_back(vec4(0, 0, 0,1));
	colori.push_back(vec4(0, 0, 0,1));
	colori.push_back(vec4(1, 0, 0,1));
	spinaGC.loadVertices(vertici, colori, GL_TRIANGLES, entityProg);
	// spine
	this->spine.init();
	/*
	FallingEntity* spinaTest = new FallingEntity;
	spinaTest->init(entityProg, UNI_entity_MatModel, spinaGC, vec2(leftWallPos.x,this->world_height), 300.0f);
	this->spine.push(spinaTest);
	*/
	return 0;
}

// TODO
void World::setupNewGame() {
	this->spine.init();
	this->player.startGame();
}

float generateTimer = 1.0;
void World::update(float deltaTime) {
	// aggiorna posizioni
	this->player.update(deltaTime);
	this->spine.update(deltaTime);
	
	// controlla collisioni
	vector<BoundingBox> bbList = this->spine.getBBlist();
	for (int i = 0; i < bbList.size(); i++) {
		if (this->player.checkCollision(bbList[i])) {
			this->spine.ignore(i);
			this->player.takeDamage();
		}
	}

	// controlla se il player è in vita, altrimenti fa perdere
	if (!this->player.isAlive()) {
		this->engine->gameLost();
		return;
	}

	// genera shuriken,spine,monete
	generateTimer -= deltaTime;
	if (generateTimer <= 0.0f) {
		FallingEntity* spinaTest = new FallingEntity;
		vec2 genPos = vec2(leftWallPos.x, this->world_height);
		bool right = false;
		if (rand() % 2 != 0) {
			genPos.x = rightWallPos.x;
			right = true;
		}
		spinaTest->init(entityProg, UNI_entity_MatModel, spinaGC, genPos, right, fallingSpeed);
		this->spine.push(spinaTest);
		generateTimer = randomFloat() * genDelta + 1.0;
		genDelta -= genDecrease;
		if (fallingSpeed < maxSpeed)
			fallingSpeed += speedIncrease;
	}
}

void World::render(float time) {
	// update del tempo alle shader
	glUseProgram(skyProg);
	glUniform1f(UNI_skyProg_currentTime, time);
	glUseProgram(wallProg);
	glUniform1f(UNI_wallProg_currentTime, time);

	// render sfondo
	glClearColor(bg_R, bg_G, bg_B, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	sky.render();
	
	glUseProgram(wallProg);
	vec3 offset = vec3(-1.85, 0., 0.);
	glUniform3fv(UNI_wallProg_offset, 1, value_ptr(offset));
 	wall.render();
	offset = vec3(1.85, 0., 0.);
	glUniform3fv(UNI_wallProg_offset, 1, value_ptr(offset));
	wall.render();
	
	// render monete, ostacoli
	this->spine.render(time);

	// render player
	this->player.render(time);
	
	// render UI
	
}

void World::terminate() {
	// deletes shader programs
	glDeleteProgram(skyProg);
	glDeleteProgram(wallProg);
	glDeleteProgram(entityProg);

	// deletes VAO buffers
	this->sky.deleteBuffers();
	this->wall.deleteBuffers();
	this->player.destroy();
}

void World::INPUT_movePlayer() {
	this->player.changeLato();
}
