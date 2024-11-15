#pragma once

/*
#pragma once //: È una direttiva che indica al compilatore di includere il file una sola volta per unità di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file già inclusi.
//Non è parte dello standard C++, quindi la sua disponibilità e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, è supportata dalla maggior parte dei compilatori moderni.
*/

#define SHADER_FOLDER "src/shaders/"

class ShaderMaker
{
    public:
		static GLuint createProgram(const char* vertexfilename, const char *fragmentfilename);
		static char* readShaderSource(const char* shaderFile);
	
    private:
		ShaderMaker() { }	
};