#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

// Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//void checkForShaderErrors(unsigned int shader, const char* shaderName);
//void checkForShaderProgramErrors(unsigned int shaderProgram, const char* shaderProgramName = "");

const char* vertexShaderSource =	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"layout (location = 1) in vec3 inColour;\n"
									"out vec3 vertexColour;\n"
									"void main()\n"
									"{\n"
									"   gl_Position = vec4(aPos, 1.0);\n"
									"   vertexColour = inColour;\n"
									"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
									"out vec4 FragColour;\n"
									"in vec3 vertexColour;\n"
									"void main()\n"
									"{\n"
									"	FragColour = vec4(vertexColour, 1);\n"
									"}\0";

int main(int argc, char* argv[]) {
	Shader shader;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "Kwame is great!", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD?
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(10, 10, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	float vertices[] = {
		// positions         // colors
		 -1, -1, 0.0f,  1.0f, 0.0f, 0.0f,   
		 -1, 1, 0.0f,  0.0f, 1.0f, 0.0f,   
		 1,  1, 0.0f,  0.0f, 0.0f, 1.0f,
		 1,  -1, 0.0f,  0.0f, 1.0f, 1.0f    
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glUseProgram(shaderProgram);
	shader.load("vertexTest.shader", "mandelbrot.shader");
	shader.use();

	int shaderProgram = shader.getShaderProgram();
	//int xOffsetLocation = glGetUniformLocation(shaderProgram, "xOffset");
	//float xOffset = -1, tk=glfwGetTime();

	// Loop!
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);

		//if (glfwGetTime() - tk > 0.01) {
		//	xOffset += 0.005;
		//	tk = glfwGetTime();
		//}
		//glUniform1f(xOffsetLocation, xOffset);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
