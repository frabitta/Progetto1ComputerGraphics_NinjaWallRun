#pragma once
#define SHADER_FOLDER "src/shaders/"

/* utility to create shader programs */
class ShaderMaker
{
    public:
		static GLuint createProgram(const char* vertexfilename, const char *fragmentfilename);
		static char* readShaderSource(const char* shaderFile);
	
    private:
		ShaderMaker() { }	
};