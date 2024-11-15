#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>
#include "ShaderMaker.h"

#pragma warning(disable:4996)
char* ShaderMaker::readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

GLuint ShaderMaker::createProgram(const char* vertexfilename, const char *fragmentfilename)
{
	int success;
	char infoLog[512];
	char vPath[100] = SHADER_FOLDER;
	char fPath[100] = SHADER_FOLDER;
	strcat(vPath, vertexfilename);
	strcat(fPath, fragmentfilename);
 
	// vertex shader
	GLchar* VertexShader = readShaderSource(vPath);							// lettura dello shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);				// creazione dello shader id
	glShaderSource(vertexShaderId, 1, (const char**)&VertexShader, NULL);	// assegnazione codice-id
	glCompileShader(vertexShaderId);										// compilazione shader
	// verifico errori
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	const GLchar* FragmentShader = readShaderSource(fPath);						// lettura dello shader
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);				// creazione dello shader id
	glShaderSource(fragmentShaderId, 1, (const char**)&FragmentShader, NULL);	// assegnazione codice-id
	glCompileShader(fragmentShaderId);											// compilazione shader
	// verifico errori
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
 
	//Creiamo un identificativo di un eseguibile e gli colleghiamo i due shader compilati
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	
	return programId;
}
