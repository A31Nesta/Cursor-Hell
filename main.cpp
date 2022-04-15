// Cursor Hell
#include "CHEngine.hpp"
#include "SpiralScene.hpp"

int main()
{
	if (!InitEngine())
	{
		std::cout << "What kind of potato are you using??" << std::endl;
		return -1;
	}
	std::cout << "Engine initialized!" << std::endl;


	SpiralScene scene;

	while (!glfwWindowShouldClose(window))
	{
		CalcFPS();
		ProcessInput();

		scene.Draw(shader, deltaTime);

		EndUpdate();
	}

	glfwTerminate();
}