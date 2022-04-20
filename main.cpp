// Cursor Hell
#include "curserSrc/CHEngine.hpp"
#include "curserSrc/CHPlayerFuncs.hpp"
#include "curserSrc/SpiralScene.hpp"
#include "curserSrc/Types/Bullet.hpp"

int main()
{
	if (!InitEngine(1))
	{
		std::cout << "What kind of potato are you using??" << std::endl;
		return -1;
	}
	std::cout << "Engine initialized!" << std::endl;

	//sp.SayTotalScore(&sounds, 420);

	SetupPlayer();

	sensitivity = 0.1f;
	SpiralScene scene(&pv, &sounds, &sp);

	while (!glfwWindowShouldClose(window))
	{
		CalcFPS();
		ProcessInput();

		UpdatePlayerRelated();
		
		scene.Draw(shader, deltaTime);
		DrawPlayerRelated();
		DrawInterface();
		DrawText();

		EndUpdate();
	}

	glfwTerminate();
}