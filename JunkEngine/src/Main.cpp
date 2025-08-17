#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

static const float PI = 3.1415962;

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

	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Vertex data
	float vertices[] = {							// texture
		// world positions		// colours			// co-ordinates
		 -0.75, -0.75, 0.0,		1.0, 0.0, 0.0,		0.0, 0.0,	// bottom-left
		 -0.75,  0.75, 0.0,		0.0, 1.0, 0.0,		0.0, 2.0,	// top-left
		  0.75,  0.75, 0.0,		0.0, 0.0, 1.0,		2.0, 2.0,	// top-right
		  0.75, -0.75, 0.0,		0.0, 1.0, 1.0,		2.0, 0.0,	// bottom-right
	};
	unsigned int indices[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};

	// load texture
	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* textureData = stbi_load("face.png", &width, &height, &numChannels, 0);

	if (!textureData) {
		printf("Oh no! Couldn't load texture file!\n");
		return -3;
	}
	printf("Width: %d Height: %d Num Channels: %d\n", width, height, numChannels);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, numChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData);

	unsigned char* textureData2 = stbi_load("Netscape.png", &width, &height, &numChannels, 0);

	if (!textureData2) {
		printf("Oh no! Couldn't load texture file!\n");
		return -3;
	}
	printf("Width: %d Height: %d Num Channels: %d\n", width, height, numChannels);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData2);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture co-ordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	shader.load("transform.vshader", "texture.fshader");
	shader.use();

	glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture2"), 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// Matrix stuff
	glm::mat4 identity = glm::mat4(1);
	glm::mat4 trans;
	//trans = glm::rotate(identity, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
	unsigned int transformLoc = glGetUniformLocation(shader.getShaderID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	float startTime = glfwGetTime();

	// Loop!
	while (!glfwWindowShouldClose(window))
	{
		float elapsedTime = glfwGetTime() - startTime;
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		
		trans = glm::rotate(identity, glm::radians(90 * elapsedTime*1.5f), glm::vec3(0.0, 1.0, 1.0));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		shader.setFloat("mixAmount", sin(elapsedTime * PI / 2) / 2 + 0.5);
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
