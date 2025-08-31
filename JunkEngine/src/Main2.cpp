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
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window, double deltaTime);

static const float PI = 3.1415962f;
static int SCR_WIDTH = 800;
static int SCR_HEIGHT = 600;

static glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
static glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

static double prevTime;

int main2(int argc, char* argv[]) {
	Shader shader;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Kwame is great!", NULL, NULL);

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

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	float g = 1.6180339887f;
	// Vertex data
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0, 1.0, 1.0, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0, 1.0, 1.0, 0.0f, 1.0f
	};

	//  0.0,    g, -1.0, 1.0, 1.0, 1.0, 0.0, 0.0, // A 
	//  0.0,    g,  1.0, 1.0, 1.0, 1.0, 0.0, 0.0, // B
	// -1.0,  0.0,    g, 1.0, 1.0, 1.0, 0.0, 0.0, // C
	//   -g, -1.0,  0.0, 1.0, 1.0, 1.0, 0.0, 0.0, // D
	// -1.0,  0.0,   -g, 1.0, 1.0, 1.0, 0.0, 0.0, // E
	//   -g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.0, 0.0, // F
	//  0.0,   -g, -1.0, 1.0, 1.0, 1.0, 0.0, 0.0, // G
	//  0.0,   -g,  1.0, 1.0, 1.0, 1.0, 0.0, 0.0, // H
	//    g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.0, 0.0, // I
	//  1.0,  0.0,   -g, 1.0, 1.0, 1.0, 0.0, 0.0,  // J
	//    g, -1.0,  0.0, 1.0, 1.0, 1.0, 0.0, 0.0,  // K
	//  1.0,  0.0,    g, 1.0, 1.0, 1.0, 0.0, 0.0,  // L

	float sin36 = 0.5878, sin108 = 0.9510, sin252 = -0.9510, sin324 = -0.5878;
	float cos36 = 0.8090, cos108 = -0.3090, cos252 = -0.3090, cos324 = 0.8090;

	float sin72 = 0.9510, sin144 = 0.5878, sin216 = -0.5878, sin288 = -0.9510;
	float cos72 = 0.3090, cos144 = -0.8090, cos216 = -0.8090, cos288 = 0.3090;
	float icosahedron[] = {
		//// Fan
		//  -g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 0.5, // F5
		// 0.0,    g, -1.0, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // A0
		// 0.0,    g,  1.0, 1.0, 1.0, 1.0, (sin36 + 1) / 2, (cos36 + 1) / 2, // B1
		//-1.0,  0.0,    g, 1.0, 1.0, 1.0, (sin108 + 1) / 2, (cos108 + 1) / 2, // C2
		//  -g, -1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 0.0, // D3
		//-1.0,  0.0,   -g, 1.0, 1.0, 1.0, (sin252 + 1) / 2, (cos252 + 1) / 2, // E4
		// 0.0,    g, -1.0, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // A0

		// // Fan
		//   g, -1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 0.5, // K10
		//   g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 1.0, // I8
		// 1.0,  0.0,   -g, 1.0, 1.0, 1.0, (sin72 + 1) / 2, (cos72 + 1) / 2, // J9
		// 0.0,   -g, -1.0, 1.0, 1.0, 1.0, (sin144 + 1) / 2, (cos144 + 1) / 2, // G6
		// 0.0,   -g,  1.0, 1.0, 1.0, 1.0, (sin252 + 1) / 2, (sin252 + 1) / 2, // H7
		// 1.0,  0.0,    g, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // L11
		//   g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 1.0, // I8

		//   // Strip
		//   0.0,    g, -1.0, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // A0
		//	 g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 1.0, // I8
		//   0.0,    g,  1.0, 1.0, 1.0, 1.0, (sin36 + 1) / 2, (cos36 + 1) / 2, // B1
		//   1.0,  0.0,    g, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // L11
		//  -1.0,  0.0,    g, 1.0, 1.0, 1.0, (sin108 + 1) / 2, (cos108 + 1) / 2, // C2
		//   0.0,   -g,  1.0, 1.0, 1.0, 1.0, (sin252 + 1) / 2, (sin252 + 1) / 2, // H7
		//	-g, -1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 0.0, // D3
		//   0.0,   -g, -1.0, 1.0, 1.0, 1.0, (sin144 + 1) / 2, (cos144 + 1) / 2, // G6
		//  -1.0,  0.0,   -g, 1.0, 1.0, 1.0, (sin252 + 1) / 2, (cos252 + 1) / 2, // E4
		//   1.0,  0.0,   -g, 1.0, 1.0, 1.0, (sin72 + 1) / 2, (cos72 + 1) / 2, // J9
		//   0.0,    g, -1.0, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // A0
		//	 g,  1.0,  0.0, 1.0, 1.0, 1.0, 0.5, 1.0, // I

	0.0, g, -1.0, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // A
	0.0, g, 1.0, 1.0, 1.0, 1.0, (sin36 + 1) / 2, (cos36 + 1) / 2, // B
	-1.0, 0.0, g, 1.0, 1.0, 1.0, (sin108 + 1) / 2, (cos108 + 1) / 2, // C
	-g, -1.0, 0.0, 1.0, 1.0, 1.0, 0.5, 0.0, // D
	-1.0, 0.0, -g, 1.0, 1.0, 1.0, (sin252 + 1) / 2, (cos252 + 1) / 2, // E
	-g, 1.0, 0.0, 1.0, 1.0, 1.0, 0.5, 0.5, // F
	0.0, -g, -1.0, 1.0, 1.0, 1.0, (sin144 + 1) / 2, (cos144 + 1) / 2, // G
	0.0, -g, 1.0, 1.0, 1.0, 1.0, (sin252 + 1) / 2, (sin252 + 1) / 2, // H
	g, 1.0, 0.0, 1.0, 1.0, 1.0, 0.5, 1.0, // I
	1.0, 0.0, -g, 1.0, 1.0, 1.0, (sin72 + 1) / 2, (cos72 + 1) / 2, // J
	g, -1.0, 0.0, 1.0, 1.0, 1.0, 0.5, 0.5, // K
	1.0, 0.0, g, 1.0, 1.0, 1.0, (sin324 + 1) / 2, (cos324 + 1) / 2, // L
	};

	// Use indices here
	unsigned int indices[] = {
		 5,  0,  1,  2,  3,  4,  0, // Fan
		10,  8,  9,  6,  7, 11,  8, // Fan
		 0,  8,  1, 11,  2,  7,  3, 6, 4, 9, 0, 8 // Strip
	};

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// load texture
	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* textureData = stbi_load("originalface.jpg", &width, &height, &numChannels, 0);

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, numChannels == 4 ? GL_RGB : GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData);

	unsigned char* textureData2 = stbi_load("facesketch.jpg", &width, &height, &numChannels, 0);

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData2);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(textureData2);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	for (int i = 0; i < 12; i++) {
		icosahedron[i * 8 + 0] *= 0.25;
		icosahedron[i * 8 + 1] *= 0.25;
		icosahedron[i * 8 + 2] *= 0.25;
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(icosahedron), icosahedron, GL_STATIC_DRAW);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// colour attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture co-ordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	shader.load("perspective.vshader", "texture.fshader");
	shader.use();

	glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.getShaderID(), "texture2"), 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glEnable(GL_DEPTH_TEST);

	// Matrix stuff
	glm::mat4 identity = glm::mat4(1);
	glm::mat4 spin;
	//trans = glm::rotate(identity, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
	unsigned int modelLoc = glGetUniformLocation(shader.getShaderID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.getShaderID(), "view");
	unsigned int projectionLoc = glGetUniformLocation(shader.getShaderID(), "projection");

	glm::mat4 view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	double startTime = glfwGetTime();
	prevTime = glfwGetTime();

	// Loop!
	while (!glfwWindowShouldClose(window))
	{
		float elapsedTime = (float)(glfwGetTime() - startTime);

		processInput(window, glfwGetTime() - prevTime);
		prevTime = glfwGetTime();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.setFloat("mixAmount", sin(elapsedTime * PI / 2) / 2 + 0.5);

		const float radius = 10.0f;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		for (int i = 0; i < 10; i++) {
			spin = glm::translate(identity, cubePositions[i]);
			spin = glm::rotate(spin, glm::radians(elapsedTime * -180), glm::vec3(1.0, 0.0, 0.0));
			spin = glm::rotate(spin, glm::radians(elapsedTime * 45), glm::vec3(0.0, 1.0, 0.0));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(spin));

			glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, 0);
			glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void *)(7 * sizeof(unsigned int)));
			glDrawElements(GL_TRIANGLE_STRIP, 12, GL_UNSIGNED_INT, (void *)(14 * sizeof(unsigned int)));
		}

		glfwSwapBuffers(window);
		glfwPollEvents();


	}


	glfwTerminate();
	return 0;
}


static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 5.0f * deltaTime; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
