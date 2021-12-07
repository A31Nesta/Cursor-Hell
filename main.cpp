// Cursor Hell
#include "CHEngine.hpp"

#include "Quad.hpp"

int main()
{
	if (!InitEngine())
	{
		std::cout << "What kind of potato are you using??" << std::endl;
		return -1;
	}
	std::cout << "Engine initialized!" << std::endl;


	Quad quad;
	std::vector<Transform> transforms;

	Transform t1;
	t1.position = glm::vec2(5.0f, 0.0f);
	t1.rotation = 45;
	t1.size		= glm::vec2(2);
	transforms.push_back(t1);

	Transform t2;
	t2.position = glm::vec2(-1.25f, -2.0f);
	t2.rotation = 30;
	t2.size = glm::vec2(1.0f, 1.75f);
	transforms.push_back(t2);


	while (!glfwWindowShouldClose(window))
	{
		ProcessInput();

		// rendering
		glClearColor(0.0f, 0.12f, 0.3f, 0.2f);
		glClear(GL_COLOR_BUFFER_BIT);

		quad.Draw(shader, transforms);

		EndUpdate();
	}

	glfwTerminate();
}