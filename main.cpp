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

		// rendering
		glClearColor(0.0f, 0.05f, 0.15f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		scene.Draw(shader, deltaTime);

		EndUpdate();
	}

	glfwTerminate();
}