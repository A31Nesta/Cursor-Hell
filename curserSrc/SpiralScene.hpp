#pragma once
#include "Scene.hpp"

class SpiralScene : public Scene
{
public:
	SpiralScene(float* x, float* y, glm::mat4 projv) : Scene(x, y, projv)
	{
		LoadTexture("Assets/Sprites/Cursor.png");
		InitScene();
	}

	void InitScene();

	void Draw(unsigned int& shader, GLFWwindow* window, double dt);

private:
	void Update(double dt);
};

