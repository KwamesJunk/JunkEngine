#pragma once
#include <stdio.h>

class Shader {
private:
	unsigned int shaderProgram;
	void shaderErrorCheck(unsigned int shader, const char* shaderName = "unnamed shader");
	void shaderProgramErrorCheck(unsigned int shader, const char* shaderName = "unnamed shader program");
public:
	void load(const char* vertexShaderFilename, const char* fragmentShaderFilename);
	void use();
	unsigned int getShaderProgram();
};
