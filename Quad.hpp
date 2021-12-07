#pragma once

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>
#include <vector>

struct Transform
{
	glm::vec2 position;
	float     rotation;
	glm::vec2 size;
};

class Quad
{
public:
	Quad();

	void Draw(unsigned int& shader, std::vector<Transform> t);

	void setTransform(Transform t) { transform = t; }

private:
	void GenerateObjects();

	Transform transform;

	unsigned int VAO, VBO, EBO;
	float vertices[12] =
	{
		 1.0f,  1.0f, 0.0f,  // top right
		 1.0f, -1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,  // bottom left
		-1.0f,  1.0f, 0.0f   // top left 
	};
	unsigned int indices[6] =
	{
		0, 1, 3,
		1, 2, 3
	};
};

