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

	sensitivity = 0.1f;
	SpiralScene scene(&xcur, &ycur, projview);

	while (!glfwWindowShouldClose(window))
	{
		CalcFPS();
		ProcessInput();
		
		scene.Draw(shader, window, deltaTime);
		DrawInterface();
		glBindTexture(GL_TEXTURE_2D, font);
		scene.DrawText(textShader);

		EndUpdate();
	}

	glfwTerminate();
}