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

	void Draw(unsigned int& shader, double dt);

private:
	void Update(double dt);
};

