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
	glfwSwapInterval(1);

	//sp.SayTotalScore(&sounds, 420);

	SetupPlayer();

	sensitivity = 0.1f;
	SpiralScene spiralScene(&pv, &sounds, &sp);
	CHPattern1 generic1(&pv, &sounds, &sp);
	CHPattern2 generic2(&pv, &sounds, &sp);

	std::vector<Scene*> scenes;
	scenes.push_back(&spiralScene);
	scenes.push_back(&generic2);
	scenes.push_back(&generic1);


	while (!glfwWindowShouldClose(window))
	{
		CalcFPS();
		ProcessInput();

		UpdatePlayerRelated();
		
		for (size_t i = 0; i < scenes.size(); i++)
		{
			uint8_t status = scenes.at(i)->Draw(shader, deltaTime);
			if (status == 1) {
				if (i == 0 && scenes.at(scenes.size()-1)->patternTimer > scenes.at(scenes.size()-1)->totalTime) {
					if (scenes.at(scenes.size()-1)->Draw(shader, deltaTime) == 2) { scenes.at(scenes.size()-1)->InitScene(); }
				}
				break;
			}
			else if (status == 3 && i == scenes.size() -1)
			{
				for (size_t j = 0; j < scenes.size()-1; j++) {
					scenes.at(j)->InitScene();
				}
			}
		}
		
		
		DrawPlayerRelated();
		DrawInterface();
		DrawText();

		EndUpdate();
	}

	glfwTerminate();
}