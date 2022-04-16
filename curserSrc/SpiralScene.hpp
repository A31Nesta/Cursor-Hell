#pragma once
#include "Scene.hpp"

class SpiralScene : public Scene
{
public:
	SpiralScene(float* x, float* y, glm::mat4 projv)
	{
		xpos = x;
		ypos = y;
		projview = projv;

		LoadTexture("Assets/Sprites/Cursor.png");
		InitScene();
	}

	void InitScene();

	void Draw(unsigned int& shader, GLFWwindow* window, double dt);

private:
	void Update(GLFWwindow* window, double dt);

	int S_X = -1, S_Y = -1;
	float* xpos;
	float* ypos;

	glm::mat4 projview;

	bool lost = false;

	glm::vec2 plPos = glm::vec2(0.0f);
	glm::vec2 plSize = glm::vec2(0.075f);
	Quad player;

	glm::vec2 origin = glm::vec2(-1, 1);
	int numberOfBullets = 0;
};

