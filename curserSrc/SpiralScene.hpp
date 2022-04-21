#pragma once
#include "Scene.hpp"

class SpiralScene : public Scene
{
public:
	SpiralScene(PlayerVars* pvars, CESoundMap* sm, CurserSoundPlayer* sp) 
		: Scene(pvars, sm, sp)
	{
		LoadTexture("Assets/Sprites/Cursor.png");
		InitScene();
	}

	void InitScene();

	uint8_t Draw(unsigned int& shader, double dt);

private:
	uint8_t Update(double dt);
};

