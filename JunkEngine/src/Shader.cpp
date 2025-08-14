#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>

void Shader::load(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
	// Load vertex shader
	std::ifstream vertexShaderSourceStream(vertexShaderFilename);
	std::string str, fileContents;
	
	if (vertexShaderSourceStream.fail()) {
		printf("Couldn't find file");
	}
	
	while (std::getline(vertexShaderSourceStream, str))
	{
		fileContents += str;
		fileContents.push_back('\n');
	}

	vertexShaderSourceStream.close();
	
	//for (int i = 0; i < fileContents.size(); i++) {
	//	putchar(fileContents.at(i));
	//}
	//putchar('*');
	
	const char* vertexShaderSource = fileContents.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	shaderErrorCheck(vertexShader, "vertex shader");

	// Load fragment shader
	fileContents = "";
	std::ifstream fragmentShaderSourceStream(fragmentShaderFilename);
	while (std::getline(fragmentShaderSourceStream, str))
	{
		fileContents += str;
		fileContents.push_back('\n');
	}

	fragmentShaderSourceStream.close();

	//for (int i = 0; i < fileContents.size(); i++) {
	//	putchar(fileContents.at(i));
	//}
	//putchar('*');

	const char* fragmentShaderSource = fileContents.c_str();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	shaderErrorCheck(fragmentShader, "fragment shader");

	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	shaderProgramErrorCheck(shaderProgram, "shaderProgram");

	// Clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::shaderErrorCheck(unsigned int shader, const char* shaderName) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << shaderName << ": ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;

		exit(-2);
	}
}

void Shader::shaderProgramErrorCheck(unsigned int shader, const char* shaderName) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << shaderName << ": ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;

		exit(-2);
	}
}

void Shader::use() {
	glUseProgram(shaderProgram);
}

unsigned int Shader::getShaderID() {
	return shaderProgram;
}

void Shader::setFloat(const char* uniformName, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, uniformName), value);
}