// Cursor Hell
#include "curserSrc/CHEngine.hpp"
#include "curserSrc/CHPlayerFuncs.hpp"
#include "curserSrc/SpiralScene.hpp"
#include "curserSrc/Patterns/GenericPatterns.hpp"
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
	SpiralScene spiralScene(&pv, &sounds, &sp);
	CHPattern1 generic1(&pv, &sounds, &sp);

	std::vector<Scene*> scenes;
	scenes.push_back(&spiralScene);
	scenes.push_back(&generic1);


	while (!glfwWindowShouldClose(window))
	{
		CalcFPS();
		ProcessInput();

		UpdatePlayerRelated();
		
		for (size_t i = 0; i < scenes.size(); i++)
		{
			if (scenes.at(i)->Draw(shader, deltaTime) == 1) { break; }
		}
		
		
		DrawPlayerRelated();
		DrawInterface();
		DrawText();

		EndUpdate();
	}

	glfwTerminate();
}