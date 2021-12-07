// Cursor Hell
#include "CHEngine.hpp"

int main()
{
	if (!InitEngine())
	{
		std::cout << "What kind of potato are you using??" << std::endl;
		return -1;
	}
	std::cout << "Engine initialized!" << std::endl;


	Scene scene;

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput();

		// rendering
		glClearColor(0.0f, 0.12f, 0.3f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawScene(scene);

		EndUpdate();
	}

	glfwTerminate();
}