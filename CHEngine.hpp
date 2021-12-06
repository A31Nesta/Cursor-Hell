#pragma once

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>


GLFWwindow* window;

int SCR_WIDTH;
int SCR_HEIGHT;


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
	/**/

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cursor Hell", glfwGetPrimaryMonitor(), NULL);
	//window = glfwCreateWindow(800, 600, "Cursor Hell", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	return true;
}

void EndUpdate()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}