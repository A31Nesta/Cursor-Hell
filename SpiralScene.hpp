#pragma once
#include "Scene.hpp"

class SpiralScene : public Scene
{
public:
	SpiralScene()
	{
		booletSprite.LoadTexture("Assets/Sprites/Cursor.png");
		InitScene();
	}

	void InitScene();

	void Draw(unsigned int& shader, double dt);

private:
	void Update(double dt);

	int numberOfBullets = 0;
};

