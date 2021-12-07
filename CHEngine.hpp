#pragma once

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>


GLFWwindow* window;

int SCR_WIDTH;
int SCR_HEIGHT;

unsigned int shader;

glm::mat4 projection = glm::mat4(1.0f);

void ProcessInput();
void CreateShader();

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool InitEngine()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	/**/
	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	
	SCR_HEIGHT = vidmode->height;
	SCR_WIDTH  = vidmode->width;

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cursor Hell", glfwGetPrimaryMonitor(), NULL);
	/**
	SCR_WIDTH  = 1280;
	SCR_HEIGHT = 720;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cursor Hell", NULL, NULL);
	/**/

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	CreateShader();

	float aspectx, aspecty;
	float gcd = std::gcd(SCR_WIDTH, SCR_HEIGHT);

	std::cout << "GCD: " << std::to_string(gcd) << std::endl;

	aspectx = SCR_WIDTH  / gcd;
	aspecty = SCR_HEIGHT / gcd;

	projection = glm::ortho(-((float)aspectx)/2, ((float)aspectx)/2, -((float)aspecty)/2, ((float)aspecty)/2, 0.1f, 100.0f);
	//projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

	return true;
}

void EndUpdate()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// Totally not stolen from learnopengl.com
void CreateShader()
{
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		""
		"out vec2 TexCoord;\n"
		""
		"uniform mat4 projection;\n"
		"uniform mat4 view;\n"
		"uniform mat4 transform;\n"
		""
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * transform * vec4(aPos, 1.0);\n"
		"   TexCoord = vec2((aPos.x+1)/2, (aPos.y+1)/2);\n"
		"}\0"
		;
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		""
		"in vec2 TexCoord;\n"
		""
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0"
		;

	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);
	// check for linking errors
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glUseProgram(shader);
}


void ProcessInput()
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}