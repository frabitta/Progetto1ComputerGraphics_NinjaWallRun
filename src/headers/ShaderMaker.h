#pragma once

/*
#pragma once //: � una direttiva che indica al compilatore di includere il file una sola volta per unit� di compilazione.
//  Il meccanismo esatto varia a seconda del compilatore, ma in generale si basa su un meccanismo interno per tenere traccia dei file gi� inclusi.
//Non � parte dello standard C++, quindi la sua disponibilit� e il comportamento preciso possono variare tra diversi compilatori. Tuttavia, � supportata dalla maggior parte dei compilatori moderni.
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