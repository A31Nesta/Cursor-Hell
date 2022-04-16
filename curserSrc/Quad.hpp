#pragma once

#include "Types/Bullet.hpp"

/** /
struct Transform
{
	glm::vec2 position = glm::vec2(0.0f);
	float     rotation = 0;
	glm::vec2 scale = glm::vec2(1.0f);

	glm::mat4 transform = glm::mat4(1.0f);
	glm::mat4 rotMatrix = glm::mat4(1.0f);

	void Translate(glm::vec2 v2)
	{
		transform = glm::translate(transform, glm::vec3(v2, 0.0f));
	}
	void Translate(float x, float y)
	{
		transform = glm::translate(transform, glm::vec3(x, y, 0.0f));
	}

	void Apply()
	{
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(position.x, position.y, 1.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(scale.x, scale.y, 1.0f));
	}
};
/**/

class Quad
{
public:
	Quad();

	void LoadTexture(std::string path);

	void ValidateQuad(unsigned int& shader);
	void Draw(unsigned int& shader, std::vector<Bullet>& t, int numberOfBullets = -1);
	void Draw(unsigned int& shader, glm::vec2 pos, glm::vec2 scale);
	void Draw();

private:
	void GenerateObjects();

	unsigned int texture;

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

