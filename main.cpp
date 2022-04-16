// Cursor Hell
#include "curserSrc/CHEngine.hpp"
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

	sensitivity = 0.5f;
	SpiralScene scene(&xoffset, &yoffset, projview);

	while (!glfwWindowShouldClose(window))
	{
		CalcFPS();
		ProcessInput();

		scene.Draw(shader, window, deltaTime);

		EndUpdate();
	}

	glfwTerminate();
}