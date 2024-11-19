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

#define MAX_SPEED 700.0f
#define FALLING_SPEED 300.0f
#define SPEED_INCREASE 5.0f
#define GEN_DELTA 2.0f
#define GEN_DECREASE 0.1f
#define GENERATE_TIMER 1.0f
#define MIN_GEN_DELTA 0.5f
#define SIDE_GEN_PROB 5

/* background and shader variables */
static const float bg_R = 0.025f, bg_G = 0.020f, bg_B = 0.11f;
static const vec4 bg_color = vec4(bg_R, bg_G, bg_B, 1.0);
static GLuint UNI_skyProg_screenRes, UNI_skyProg_currentTime;
static GLuint UNI_wallProg_screenRes, UNI_wallProg_currentTime, UNI_wallProg_offset;
static GLuint UNI_entity_MatProj, UNI_entity_MatModel;

/* spine variables */
static GraphicComponent spinaGC;
static vec2 leftWallPos;
static vec2 rightWallPos;

/* spine generation variables */
static float maxSpeed = MAX_SPEED;
static float fallingSpeed = FALLING_SPEED;
static float speedIncrease = SPEED_INCREASE;
static float genDelta = GEN_DELTA;
static float genDecrease = GEN_DECREASE;
static float generateTimer = GENERATE_TIMER;
static float minGenDelta = MIN_GEN_DELTA;
static int sideGenProb = SIDE_GEN_PROB;

float randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

int World::init(const int height, const int width, Engine* engine) {
	this->engine = engine;
	this->world_width = (float)width;
	this->world_height = (float)height;
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
	leftWallPos = vec2(this->world_width * 0.109 , this->world_width * 0.10);
	rightWallPos = vec2(this->world_width - this->world_width * 0.109, this->world_width * 0.10);
	// player
	this->player.init(entityProg, UNI_entity_MatModel, leftWallPos, rightWallPos);
	// spina GC
	/*
	init_plane(vertici, colori,vec2(-1.,-1),vec2(+1.,+1.),vec4(1.,0.5,0.,1.));
	spinaGC.loadVertices(vertici, colori, GL_TRIANGLE_FAN, entityProg);
	*/
	init_triangle(vertici, colori);
	spinaGC.loadVertices(vertici, colori, GL_TRIANGLES, entityProg);
	// spine
	this->spine.init();

	return 0;
}

// TODO
void World::setupNewGame() {
	this->spine.init();
	this->player.startGame();
	maxSpeed = MAX_SPEED;
	fallingSpeed = FALLING_SPEED;
	speedIncrease = SPEED_INCREASE;
	genDelta = GEN_DELTA;
	genDecrease = GEN_DECREASE;
	generateTimer = GENERATE_TIMER;

	this->world_StartTime = (float)glfwGetTime();
}

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
		this->engine->gameLost((int)floor(glfwGetTime() - this->world_StartTime));
		return;
	}

	// genera shuriken,spine,monete
	generateTimer -= deltaTime;
	if (generateTimer <= 0.0f) {
		FallingEntity* spinaTemp = new FallingEntity;
		vec2 genPos = vec2(leftWallPos.x, this->world_height);
		bool right = false;
		int electedSide = rand() % 10;
		if (electedSide > sideGenProb) {
			genPos.x = rightWallPos.x;
			right = true;
			if (sideGenProb < 10) {
				sideGenProb += 1;
			}
		}
		else {
			if (sideGenProb > 0) {
				sideGenProb -= 1;
			}
		}
		spinaTemp->init(entityProg, UNI_entity_MatModel, spinaGC, genPos, right, fallingSpeed);
		this->spine.push(spinaTemp);
		generateTimer = randomFloat() * genDelta + 0.3 * (maxSpeed - fallingSpeed) / 400.0f + 0.13f;
		if (genDelta > minGenDelta)
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
